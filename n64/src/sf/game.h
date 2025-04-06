#pragma once

#include "n64/types.h"

typedef enum TeamId {
  TEAM_ID_FOX,
  TEAM_ID_FALCO,
  TEAM_ID_SLIPPY,
  TEAM_ID_PEPPY,
  TEAM_ID_KATT,
  TEAM_ID_BILL,
  TEAM_ID_MAX,
} sf_team_id_t;

typedef struct {
  u8 _unknown_0x000_0x21F[0x21F];
  s32 radioDamageTimer;
  u8 _unknown_0x224_0x263[0x03F];
  s32 shields;
} sf_player_t;

#define sf_team_shields ((s32*)0x801778B0)
#define sf_saved_team_shields ((s32*)0x801778D0)
#define sf_total_hits (*(s32*)0x80161714)
#define sf_mission_hits ((s32*)0x80177B70)
#define sf_player (*(sf_player_t**)0x80178280)
#define sf_pause_action (*(s32*)0x80161810)
#define sf_pause_selection (*(s32*)0x80161814)
#define sf_pause_timer (*(s32*)0x80161838)

typedef int (*sf_fnt_game_update)();
#define sf_fn_game_update ((sf_fnt_game_update)0x800A26C0)

typedef s32 (*sf_fnt_pause_check_joystick)();
#define sf_fn_pause_check_joystick ((sf_fnt_pause_check_joystick)0x800886B8)
