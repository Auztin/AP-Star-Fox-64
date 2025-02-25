#pragma once

#include "n64/types.h"

typedef enum {
  SCENE_TITLE,
  SCENE_MENU,
  SCENE_MAP,
  SCENE_GAME_OVER,
  SCENE_CREDITS,
  SCENE_CORNERIA,
  SCENE_METEO,
  SCENE_TITANIA,
  SCENE_SECTOR_X,
  SCENE_AQUAS,
  SCENE_AREA_6,
  SCENE_FORTUNA,
  SCENE_UNK_4,
  SCENE_SECTOR_Y,
  SCENE_SOLAR,
  SCENE_ZONESS,
  SCENE_VENOM_ANDROSS,
  SCENE_TRAINING,
  SCENE_VENOM_1,
  SCENE_KATINA,
  SCENE_20,
  SCENE_MACBETH,
  SCENE_BOLSE,
  SCENE_SECTOR_Z,
  SCENE_VENOM_2,
  SCENE_VERSUS = 50,
  SCENE_LOGO = 99,
} sf_scenes_t;

#define sf_current_scene (*(s32*)0x801774F8)

typedef bool (*sf_fnt_load_scene_data)(sf_scenes_t scene, u8 _unk);
#define sf_fn_load_scene_data ((sf_fnt_load_scene_data)0x80058F14)
