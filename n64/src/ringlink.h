#pragma once

#include "n64/types.h"
#include <string.h>

typedef struct{
    u32 timer;
    s16 rings;
}ring_batch_t;

typedef enum {
    RINGLINK_STATE_IDLE,
    RINGLINK_STATE_ZERO_OUT,
    RINGLINK_STATE_HOLDING_BATCH,
    RINGLINK_STATE_HOLDING_NEGATIVE_BATCH,
    RINGLINK_STATE_HOLDING_BOSS_BATCH,
    RINGLINK_STATE_TRANSMIT_READY,
} ringlink_state_t;

static ringlink_state_t ringlink_state = RINGLINK_STATE_IDLE;
static ring_batch_t ring_batch;

void ringlink_update();
void batch_rings(s16 amount);
void prep_ring_transmission(bool force);
void transmit_ring_message();

void get_ringlink_state_str(char* buf);
bool is_player_transitioning_state(sf_player_state_t from, sf_player_state_t to);
