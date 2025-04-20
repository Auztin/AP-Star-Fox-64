#pragma once

#include "n64/types.h"
#include "sf/scene.h"

typedef struct {
  bool inited;
  bool check;
  bool ignore_rewards;
} map_t;
extern map_t map;

void map_load_scene_data(sf_scenes_t scene);
