#pragma once

#include "n64/types.h"
#include "sf/game.h"

typedef enum {
  RINGLINK_STATE_IDLE,
  RINGLINK_STATE_ZERO_OUT,
  RINGLINK_STATE_HOLDING_BATCH,
  RINGLINK_STATE_HOLDING_NEGATIVE_BATCH,
  RINGLINK_STATE_HOLDING_BOSS_BATCH,
  RINGLINK_STATE_TRANSMIT_READY,
} ringlink_state_t;

typedef struct {
  ringlink_state_t state;
  u16 last_player_hits;
  struct {
    s16 rings;
    u32 timer;
  } batch;
} ringlink_t;
extern ringlink_t ringlink;

void ringlink_update();
bool ringlink_transmit();
void ringlink_get_state(char* buf);
