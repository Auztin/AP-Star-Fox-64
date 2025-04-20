#pragma once

#include "n64/types.h"

typedef struct {
  u8 a : 1;
  u8 b : 1;
  u8 z : 1;
  u8 start : 1;
  u8 dup : 1;
  u8 ddown : 1;
  u8 dleft : 1;
  u8 dright : 1;

  u8 _unused : 2;
  u8 l : 1;
  u8 r : 1;
  u8 cup : 1;
  u8 cdown : 1;
  u8 cleft : 1;
  u8 cright : 1;

  struct {
    s8 x;
    s8 y;
  } joystick;
} sf_controller_t;

#define sf_controllers_held ((sf_controller_t*)0x800DD880)
#define sf_controllers_pressed ((sf_controller_t*)0x800DD898)
#define sf_controller_timeout (*(u32*)0x800DD8B4)
#define sf_active_controller_pressed (*(sf_controller_t**)0x8017797C)
