#pragma once

#include "n64/types.h"

typedef struct{
    u32 timer;
    s16 rings;
}ring_batch_t;

static ring_batch_t ring_batch;

void ringlink_update();
void batch_rings(s16 amount);
void send_ring_batch(bool force);