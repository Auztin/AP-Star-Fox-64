#pragma once

#include "n64/types.h"

typedef struct {
  float x;
  float y;
  float z;
} sf_vec3f_t;

typedef enum {
  GSTATE_NONE,
  GSTATE_INIT,
  GSTATE_TITLE,
  GSTATE_MENU,
  GSTATE_MAP,
  GSTATE_GAME_OVER,
  GSTATE_VS_INIT,
  GSTATE_PLAY,
  GSTATE_ENDING,
  GSTATE_BOOT = 100,
  GSTATE_BOOT_WAIT,
  GSTATE_SHOW_LOGO,
  GSTATE_CHECK_SAVE,
  GSTATE_LOGO_WAIT,
  GSTATE_START,
} sf_game_state_t;

#define sf_cur_state (*(sf_game_state_t*)0x80177834)
#define sf_next_state (*(s16*)0x80161A32)
#define sf_last_state (*(s16*)0x80161A34)
#define sf_video_features1 (*(u32*)0x800C7EEC)
#define sf_video_features2 (*(u32*)0x800C7F1C)
