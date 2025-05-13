#pragma once

#include "sf/objects.h"

typedef struct {
  s16 id;
  sf_item_t* last_item;
  s16 last_ap_id;
} object_t;
extern object_t object;

void object_item_init(sf_item_t* item);
void object_item_load(sf_item_t* item, sf_object_init_t* init);
void object_info(sf_object_info_t* info, u32 id);
void object_item_drop(sf_actor_t* actor);
void object_draw_silver_ring(sf_item_t* item);
void object_collect_silver_ring(sf_item_t* item);
