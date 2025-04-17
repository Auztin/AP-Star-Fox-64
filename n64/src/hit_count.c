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
}

void send_ring_batch(bool force){
  ring_batch.timer += main.delta;
  if (force) goto send;

  if (ring_batch.timer < RING_BATCH_FREQUENCY) return;
  if (ring_batch.rings == 0) return;
  if (ap.output.cmd != AP_CMD_NONE) return;

  send:
  ap.output.bounce_packet.header = AP_ITEM_RING_LINK;
  ap.output.bounce_packet.data = ring_batch.rings;
  ap.output.cmd = AP_CMD_BOUNCE;
  ap.output.size = 6;

  ring_batch.timer = 0;
  ring_batch.rings = 0;
}

void ringlink_update(){ // Runs each tick
  if(is_player_transitioning_state(PLAYER_STATE_INIT, PLAYER_STATE_ACTIVE)){
    u16 pre_death_player_hits = main.last_player_hits;
    batch_rings(sf_target_hits - pre_death_player_hits);
    main.last_player_hits = sf_target_hits;
  }
  if (sf_player->state == PLAYER_STATE_ACTIVE) {
    // Hit counter went up, batch them up for next ringlink packet
    if(main.last_player_hits < sf_target_hits){
      batch_rings(sf_target_hits - main.last_player_hits);
      main.last_player_hits = sf_target_hits;
    }
    send_ring_batch(false);
  }

  if (is_player_transitioning_state(PLAYER_STATE_ACTIVE,
                                    PLAYER_STATE_LEVEL_COMPLETE)){
    // This state change catches the boss hit bonus
    batch_rings(sf_target_hits - main.last_player_hits);
    send_ring_batch(true);
    main.last_player_hits = 0;
  }
}