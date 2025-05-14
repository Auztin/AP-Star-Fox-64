#pragma once

#include "n64/types.h"
#include "global.h"

typedef enum {
  MISSION_COMPLETE,
  MISSION_ACCOMPLISHED,
  MISSION_WARP,
} sf_mission_status_t;

typedef enum {
  LEVEL_FLAG_PLAYED,
  LEVEL_FLAG_MEDAL,
  LEVEL_FLAG_CLEAR
} sf_level_flag_t;

typedef enum {
  LEVEL_UNK_M1 = -1,
  LEVEL_CORNERIA,
  LEVEL_METEO,
  LEVEL_SECTOR_X,
  LEVEL_AREA_6,
  LEVEL_UNK_4,
  LEVEL_SECTOR_Y,
  LEVEL_VENOM_1,
  LEVEL_SOLAR,
  LEVEL_ZONESS,
  LEVEL_VENOM_ANDROSS,
  LEVEL_TRAINING,
  LEVEL_MACBETH,
  LEVEL_TITANIA,
  LEVEL_AQUAS,
  LEVEL_FORTUNA,
  LEVEL_UNK_15,
  LEVEL_KATINA,
  LEVEL_BOLSE,
  LEVEL_SECTOR_Z,
  LEVEL_VENOM_2,
  LEVEL_VERSUS,
  LEVEL_WARP_ZONE = 77,
} sf_level_t;

typedef enum {
  PLANET_NONE=-1,
  PLANET_METEO,
  PLANET_AREA_6,
  PLANET_BOLSE,
  PLANET_SECTOR_Z,
  PLANET_SECTOR_X,
  PLANET_SECTOR_Y,
  PLANET_KATINA,
  PLANET_MACBETH,
  PLANET_ZONESS,
  PLANET_CORNERIA,
  PLANET_TITANIA,
  PLANET_AQUAS,
  PLANET_FORTUNA,
  PLANET_VENOM,
  PLANET_SOLAR,
  PLANET_MAX,
} sf_planet_id_t;

typedef enum {
  PL_PATH_BLU,
  PL_PATH_YLW,
  PL_PATH_RED,
  PL_WARP_YLW,
  PL_WARP_RED,
} sf_path_color_t;

typedef struct {
  sf_planet_id_t id;
  sf_vec3f_t _unk_0x04;
  sf_vec3f_t pos;
  float _unk_0x1C;
  float _unk_0x20;
  s32 alpha;
  s32 _unk_0x28;
  union {
    struct {
      sf_planet_id_t complete;
      sf_planet_id_t accomplished;
      sf_planet_id_t warp;
    } dest;
    sf_planet_id_t dests[3];
  };
} sf_planet_t;

typedef struct {
  sf_path_color_t color;
  sf_planet_id_t start;
  sf_planet_id_t end;
  s32 _unk_0x0C[2];
  s32 ship;
  s32 alpha;
} sf_path_t;

#define sf_map_mission_status (*(u8*)0x80177930)
#define sf_map_planets ((sf_planet_t*)0x801AF4A0)
#define sf_map_counter (*(u32*)0x801CD9C4)
#define sf_map_state (*(u32*)0x801CD944)
#define sf_map_show_menu (*(u32*)0x801CEFC4)
#define sf_map_cutscene_state (*(u32*)0x801CEED8)
#define sf_map_last_state (*(u16*)0x80161A34)
#define sf_map_camera_pos ((sf_vec3f_t*)0x801CEEE8)
#define sf_map_camera_look ((sf_vec3f_t*)0x801CEF58)
#define sf_map_previous_planet (*(sf_planet_id_t*)0x801CD950)
#define sf_map_current_planet (*(sf_planet_id_t*)0x801CD954)
#define sf_map_next_planet (*(sf_planet_id_t*)0x801CD958)
#define sf_map_mission_list ((sf_planet_id_t*)0x80177B90)
#define sf_map_current_mission (*(u32*)0x80177B48)
#define sf_map_no_menu (*(u32*)0x801CEFD0)
#define sf_map_level_id (*(sf_level_t*)0x80178234)
#define sf_map_level_start_state (*(u32*)0x801B8280)
#define sf_map_path_types ((u32*)0x80177BD8)
#define sf_map_paths ((sf_path_t*)0x801AFD18)
#define sf_map_venom_hard_clear (*(u8*)0x800D2F68)
#define sf_map_ship_anim_state (*(u32*)0x801CEEA4)

typedef int (*sf_fnt_set_level_flag)(sf_level_t level, sf_level_flag_t flag);
#define sf_fn_set_level_flag ((sf_fnt_set_level_flag)0x8019FD1C)

typedef int (*sf_fnt_map_idle)();
#define sf_fn_map_idle ((sf_fnt_map_idle)0x801AD11C)

typedef int (*sf_fnt_map_set_level_id)();
#define sf_fn_map_set_level_id ((sf_fnt_map_set_level_id)0x801A6368)

typedef int (*sf_fnt_map_select_level)();
#define sf_fn_map_select_level ((sf_fnt_map_select_level)0x801A659C)
