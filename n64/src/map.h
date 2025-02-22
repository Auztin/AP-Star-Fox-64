#pragma once

#include "n64/types.h"

typedef struct {
  bool inited;
  bool check;
} map_t;
extern map_t map;

void map_load_scene_data();
