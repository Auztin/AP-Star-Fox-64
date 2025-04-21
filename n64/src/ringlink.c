#include "ringlink.h"
#include "main.h"
#include "ap/ap.h"
#include "ap/commands.h"
#include <string.h>

#define RING_BATCH_FREQUENCY 250

ringlink_t ringlink = {0, };

bool ringlink_player_changing_state(sf_player_state_t from, sf_player_state_t to) {
  if (!sf_player) return false;
  return (main.last_player_state == from && sf_player->state == to);
}

// Hits accumulate and send in batches for RingLink
void ringlink_batch_rings(s16 amount) {
  if (amount == 0) return;
  if (ringlink.batch.rings == 0) ringlink.batch.timer = 0;
  ringlink.batch.rings += amount;
  ringlink.state = RINGLINK_STATE_HOLDING_BATCH;
}

bool ringlink_transmit() {
  // runs each tick from ap_output(). Do not call directly.
  if (ringlink.state != RINGLINK_STATE_TRANSMIT_READY) return false;
  ap.output.cmd = AP_CMD_RINGLINK;
  ap.output.ringlink = ringlink.batch.rings;
  ap.output.size = 4;
  ringlink.batch.timer = 0;
  ringlink.batch.rings = 0;
  ringlink.state = RINGLINK_STATE_IDLE;
  return true;
}

void ringlink_prep_transmission(bool force) {
  // Set the state machine to queue up a ring link message,
  // if requirements are satisfied.
  if (force) goto send;
  if (ringlink.batch.timer < RING_BATCH_FREQUENCY) return;
  if (ringlink.batch.rings == 0) return;
  send:
  ringlink.state = RINGLINK_STATE_TRANSMIT_READY;
}

void ringlink_update() { // Runs each tick
  ringlink.batch.timer += main.delta;
  if (sf_player && sf_player->state == PLAYER_STATE_ACTIVE && ringlink.last_player_hits < sf_hits) {
    // Hit counter went up, batch them up for next ringlink packet
    ringlink_batch_rings(sf_hits - ringlink.last_player_hits);
  }
  if (ringlink_player_changing_state(PLAYER_STATE_ACTIVE, PLAYER_STATE_DOWN)) { // died
    if (sf_lives <= 0) { // Game over special case.
      ringlink_batch_rings(-sf_hits);
      ringlink_prep_transmission(true);
    }
    else ringlink.state = RINGLINK_STATE_HOLDING_NEGATIVE_BATCH;
  }
  if (ringlink_player_changing_state(PLAYER_STATE_ACTIVE, PLAYER_STATE_LEVEL_COMPLETE)) {
    ringlink.state = RINGLINK_STATE_HOLDING_BOSS_BATCH;
  }
  switch (ringlink.state) {
    case RINGLINK_STATE_ZERO_OUT:
      sf_total_hits = sf_displayed_hits = ringlink.last_player_hits = 0;
      ringlink.state = RINGLINK_STATE_IDLE;
      break;
    case RINGLINK_STATE_HOLDING_BATCH:
      ringlink_prep_transmission(false);
      break;
    case RINGLINK_STATE_HOLDING_NEGATIVE_BATCH:
      // Runs when player respwans for negative ring link
      if (ringlink_player_changing_state(PLAYER_STATE_INIT, PLAYER_STATE_ACTIVE)) {
        ringlink_batch_rings(sf_hits - ringlink.last_player_hits);
      }
      break;
    case RINGLINK_STATE_HOLDING_BOSS_BATCH:
      ringlink_batch_rings(sf_hits - ringlink.last_player_hits);
      ringlink_prep_transmission(true);
      break;
    case RINGLINK_STATE_IDLE:
    default:
  }
  ringlink.last_player_hits = sf_hits;
}

void ringlink_get_state(char* buf) {
  // Helpful for debugging
  switch(ringlink.state) {
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
