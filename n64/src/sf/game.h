#pragma once

#include "n64/types.h"

typedef enum {
  TEAM_ID_FOX,
  TEAM_ID_FALCO,
  TEAM_ID_SLIPPY,
  TEAM_ID_PEPPY,
  TEAM_ID_KATT,
  TEAM_ID_BILL,
  TEAM_ID_MAX,
} sf_team_id_t;

typedef enum {
  TEAM_ID_WOLF,
  TEAM_ID_LEON,
  TEAM_ID_PIGMA,
  TEAM_ID_ANDREW,
} sf_star_wolf_team_id_t;

typedef enum {
  PLAYER_STATE_STANDBY,
  PLAYER_STATE_INIT,
  PLAYER_STATE_LEVEL_INTRO,
  PLAYER_STATE_ACTIVE,
  PLAYER_STATE_DOWN,
  PLAYER_STATE_U_TURN,
  PLAYER_STATE_NEXT,
  PLAYER_STATE_LEVEL_COMPLETE,
  PLAYER_STATE_ENTER_WARP_ZONE,
  PLAYER_STATE_START_360,
  PLAYER_STATE_GFOX_REPAIR,
  PLAYER_STATE_ANDROSS_MOUTH,
  PLAYER_STATE_UNK_12,
  PLAYER_STATE_VS_STANDBY,
  PLAYER_STATE_MAX,
} sf_player_state_t;

typedef struct {
  u8 _unknown_0x000_0x1C7[0x1C7];
  sf_player_state_t state;
  u8 _unknown_0x1CC_0x21F[0x053];
  s32 radioDamageTimer;
  u8 _unknown_0x224_0x263[0x03F];
  s32 shields;
} sf_player_t;

typedef enum {
  RCID_FOX = 0,
  RCID_STATIC = 2,
  RCID_FOX_RED = 5,
  RCID_FALCO = 10,
  RCID_FALCO_RED = 15,
  RCID_SLIPPY = 20,
  RCID_SLIPPY_RED = 25,
  RCID_PEPPY = 30,
  RCID_PEPPY_RED = 35,
  RCID_KATT = 40,
  RCID_ANDROSS = 50,
  RCID_ANDROSS_RED = 55,
  RCID_JAMES = 60,
  RCID_GEN_PEPPER = 70,
  RCID_BOSS_CORNERIA = 80,
  RCID_ROB64 = 90,
  RCID_ROB64_RED = 95,
  RCID_BOSS_METEO = 100,
  RCID_BOSS_CORNERIA2 = 110,
  RCID_BOSS_AREA6 = 120,
  RCID_BOSS_ZONESS = 130,
  RCID_ROB64_2 = 140,
  RCID_BOSS_SECTORX = 150,
  RCID_BOSS_SECTORY = 160,
  RCID_BILL = 170,
  RCID_CAIMAN_AREA6 = 180,
  RCID_BOSS_MACBETH = 190,
  RCID_WOLF = 200,
  RCID_PIGMA = 210,
  RCID_LEON = 220,
  RCID_ANDREW = 230,
  RCID_WOLF_2 = 240,
  RCID_PIGMA_2 = 250,
  RCID_LEON_2 = 260,
  RCID_ANDREW_2 = 270,
  RCID_ROB64_TITLE = 300,
  RCID_GEN_PEPPER_TITLE = 310,
  RCID_TR = 350,
  RCID_FOX_EXPERT = 400,
  RCID_1000 = 1000,
} sf_radio_character_t;

typedef enum {
  LASERS_SINGLE,
  LASERS_TWIN,
  LASERS_HYPER,
} sf_laser_strength_t;

typedef struct {
  u8 padding;
  u8 peppy;
  u8 slippy;
  u8 falco;
} sf_mission_team_t;

#define sf_team_shields ((s32*)0x801778B0)
#define sf_saved_team_shields ((s32*)0x801778D0)
#define sf_prev_planet_team_shields ((s32*)0x80177C38)
#define sf_prev_planet_saved_team_shields ((s32*)0x801778F0)
#define sf_star_wolf_alive ((s32*)0x80177CD0)
#define sf_saved_star_wolf_alive ((s32*)0x80177CF0)
#define sf_hits (*(s32*)0x80161A98)
#define sf_total_hits (*(s32*)0x80161714)
#define sf_mission_hits ((s32*)0x80177B70)
#define sf_mission_medals ((s32*)0x80177BB0)
#define sf_mission_team ((sf_mission_team_t*)0x80177B50)
#define sf_mission_clear ((u8*)0x800D3180)
#define sf_player (*(sf_player_t**)0x80178280)
#define sf_pause_action (*(s32*)0x80161810)
#define sf_pause_selection (*(s32*)0x80161814)
#define sf_pause_timer (*(s32*)0x80161838)
#define sf_reset_flags (*(s32*)0x80177824)
#define sf_lives (*(s16*)0x80161AA0)
#define sf_laser_strength (*(sf_laser_strength_t*)0x80161AA8)
#define sf_gold_rings (*(u8*)0x80161A90)
#define sf_saved_gold_rings (*(u8*)0x80161A94)
#define sf_bombs (*(s32*)0x80177DA0)
#define sf_great_fox_intact (*(u8*)0x80177B8C)

typedef int (*sf_fnt_game_update)();
#define sf_fn_game_update ((sf_fnt_game_update)0x800A26C0)

typedef int (*sf_fnt_pause_check_joystick)();
#define sf_fn_pause_check_joystick ((sf_fnt_pause_check_joystick)0x800886B8)

extern void sf_fn_play_radio_message(u16* msg, sf_radio_character_t);
