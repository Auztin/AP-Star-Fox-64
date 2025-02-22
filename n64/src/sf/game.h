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

#define sf_team_shields ((s32*)0x801778B0)
#define sf_saved_team_shields ((s32*)0x801778D0)
#define sf_total_hits (*(s32*)0x80161714)
#define sf_mission_hits ((s32*)0x80177B70)

typedef int (*sf_fnt_game_update)();
#define sf_fn_game_update ((sf_fnt_game_update)0x800A26C0)
