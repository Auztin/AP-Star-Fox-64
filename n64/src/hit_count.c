#include "ap/ap.h"
#include "ap/commands.h"
#include "sf/game.h"
#include "main.h"
#include "hit_count.h"
#define RING_BATCH_FREQUENCY 250

// Hits accumulate and send in batches for RingLink
void batch_rings(s16 amount){
  if (amount == 0) return;
  if (ring_batch.rings == 0)
    ring_batch.timer = 0;

  ring_batch.rings += amount;
  ringlink_state = RINGLINK_STATE_HOLDING_BATCH;
}

void transmit_ring_message(){
  // runs each tick from ap_output(). Do not call directly.
  if (ap.output.cmd != AP_CMD_NONE) return;
  if (ringlink_state != RINGLINK_STATE_TRANSMIT_READY) return;

  ap.output.bounce_packet.header = AP_ITEM_RING_LINK;
  ap.output.bounce_packet.data = ring_batch.rings;
  ap.output.cmd = AP_CMD_BOUNCE;
  ap.output.size = 6;

  ring_batch.timer = 0;
  ring_batch.rings = 0;
  ringlink_state = RINGLINK_STATE_IDLE;
}

void prep_ring_transmission(bool force){
  // Set the state machine to queue up a ring link message,
  // if requirements are satisfied.
  if (force) goto send;
  if (ring_batch.timer < RING_BATCH_FREQUENCY) return;
  if (ring_batch.rings == 0) return;

  send:
  ringlink_state = RINGLINK_STATE_TRANSMIT_READY;
}

void ringlink_update(){ // Runs each tick
  ring_batch.timer += main.delta;

  if (sf_player && sf_player->state == PLAYER_STATE_ACTIVE) {
    // Hit counter went up, batch them up for next ringlink packet
    if(main.last_player_hits < sf_target_hits){
      batch_rings(sf_target_hits - main.last_player_hits);
    }
  }

  if (is_player_transitioning_state(PLAYER_STATE_ACTIVE,
                                    PLAYER_STATE_DOWN)){ // died
    if (sf_lives <= 0){ // Game over special case.
      batch_rings(-sf_target_hits);
      prep_ring_transmission(true);
    }else
      ringlink_state = RINGLINK_STATE_HOLDING_NEGATIVE_BATCH;
  }
  if (is_player_transitioning_state(PLAYER_STATE_ACTIVE,
                                    PLAYER_STATE_LEVEL_COMPLETE)){
    ringlink_state = RINGLINK_STATE_HOLDING_BOSS_BATCH;
  }

  switch (ringlink_state){
    case RINGLINK_STATE_ZERO_OUT:
      sf_total_hits = sf_current_hits = main.last_player_hits = 0;
      ringlink_state = RINGLINK_STATE_IDLE;
    break;
    case RINGLINK_STATE_HOLDING_BATCH:
      prep_ring_transmission(false);
    break;
    case RINGLINK_STATE_HOLDING_NEGATIVE_BATCH:
      // Runs when player respwans for negative ring link
      if (is_player_transitioning_state(PLAYER_STATE_INIT, PLAYER_STATE_ACTIVE)){
        u16 pre_death_player_hits = main.last_player_hits;
        batch_rings(sf_target_hits - pre_death_player_hits);
      }
    break;
    case RINGLINK_STATE_HOLDING_BOSS_BATCH:
      batch_rings(sf_target_hits - main.last_player_hits);
      prep_ring_transmission(true);
    break;
    case RINGLINK_STATE_IDLE:
    default:

  }

  main.last_player_hits = sf_target_hits;
}

void get_ringlink_state_str(char* buf){
  // Helpful for debugging
  switch(ringlink_state){
      case RINGLINK_STATE_IDLE:
          strcpy(buf, "RINGLINK_IDLE");
          break;
      case RINGLINK_STATE_ZERO_OUT:
          strcpy(buf, "RINGLINK_ZERO");
          break;
      case RINGLINK_STATE_HOLDING_BATCH:
          strcpy(buf, "RINGLINK_HOLD");
          break;
      case RINGLINK_STATE_HOLDING_NEGATIVE_BATCH:
          strcpy(buf, "RINGLINK_NEGHOLD");
          break;
      case RINGLINK_STATE_HOLDING_BOSS_BATCH:
          strcpy(buf, "RINGLINK_BOSS");
          break;
      case RINGLINK_STATE_TRANSMIT_READY:
          strcpy(buf, "RINGLINK_READY");
          break;
      }
}

bool is_player_transitioning_state(sf_player_state_t from, sf_player_state_t to){
  if (!sf_player) return false;
  return (main.last_player_state == from && sf_player->state == to);
}