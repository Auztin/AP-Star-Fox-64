#pragma once

#include "n64/types.h"

typedef enum {
  SAVE_METEO,
  SAVE_AREA_6,
  SAVE_BOLSE,
  SAVE_SECTOR_Z,
  SAVE_SECTOR_X,
  SAVE_SECTOR_Y,
  SAVE_KATINA,
  SAVE_MACBETH,
  SAVE_ZONESS,
  SAVE_CORNERIA,
  SAVE_TITANIA,
  SAVE_AQUAS,
  SAVE_FORTUNA,
  SAVE_SOLAR,
  SAVE_VENOM1,
  SAVE_VENOM2,
  SAVE_LEVELS_MAX,
} sf_save_level_id_t;

typedef struct {
  union {
    struct {
      u8 _unused1 : 3;
      u8 medal : 1;
      u8 clear : 1;
      u8 _unused2 : 3;
    } expert;
    struct {
      u8 _unused1 : 5;
      u8 played : 1;
      u8 medal : 1;
      u8 clear : 1;
    };
  };
} sf_save_level_t;

typedef struct {
  sf_save_level_t levels[SAVE_LEVELS_MAX];
} sf_save_t;

#define sf_save (*(sf_save_t*)0x80178870)
