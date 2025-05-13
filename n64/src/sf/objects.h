#pragma once

#include "n64/types.h"

enum {
  OBJ_ITEM_LASERS = 322,
  OBJ_ITEM_CHECKPOINT,
  OBJ_ITEM_SILVER_RING,
  OBJ_ITEM_SILVER_STAR,
  OBJ_ITEM_BOMB = 327,
  OBJ_ITEM_1UP = 335,
  OBJ_ITEM_GOLD_RING,
  OBJ_ITEM_WING_REPAIR,
};

typedef struct {
  u8 _unk_0x00_0x0F[0x10];
  s16 id;
  u8 _unk_0x12_0x13[0x02];
} sf_object_init_t;

typedef struct {
  u8 _unk_0x00_0x21[0x22];
  union {
    s16 object_index;
    s16 ap_id;
  };
} sf_object_info_t;

typedef struct {
  u8 status;
  u8 _unk_0x01;
  u16 id;
  u8 _unk_0x04_0x1B[0x18];
  sf_object_info_t info;
  u8 _unk_0x40_0x67[0x28];
  float scale;
} sf_item_t;

typedef struct {
  u8 _unk_0x00_0x01[0x02];
  u16 id;
  u8 _unk_0x04_0x1B[0x18];
  sf_object_info_t info;
} sf_actor_t;

#define sf_level_objects_index (*(u32*)0x80177DC8)

void sf_fn_object_item_init(sf_item_t* item);
void sf_fn_object_info(sf_object_info_t* info, u32 id);
void sf_fn_item_load(sf_item_t* item, sf_object_init_t* init);
void sf_fn_item_drop(sf_actor_t* actor);
void sf_fn_item_draw_silver_ring(sf_item_t* item);
