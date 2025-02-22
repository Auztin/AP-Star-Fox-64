#pragma once

#include "n64/types.h"
#include "sf/scene.h"

typedef struct {
  bool is_emulator;
  u32 last_c0_count;
  u32 delta; // milliseconds since last frame
} main_t;
extern main_t main;

void main_init();
void main_loop();
bool main_load_scene_data(sf_scenes_t scene, u8 _unk);
void main_pre_venom();
void main_goal_completed();
