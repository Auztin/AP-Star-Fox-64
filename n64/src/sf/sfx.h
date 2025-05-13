#pragma once

#include "n64/types.h"

#define SF_SFX_CURSOR           0x49000002
#define SF_SFX_ERROR            0x4900100A
#define SF_SFX_DECIDE           0x49000003
#define SF_SFX_RING             0x4900200E
#define SF_SFX_GET_EMBLEM       0x49008030
#define SF_SFX_SHIELD_UPGRADE   0x49008015

#define sf_sfx_default_pos ((float*)0x800C5D28)

typedef int (*sf_fnt_sfx_map_menu)(u8 active);
#define sf_fn_sfx_map_menu ((sf_fnt_sfx_map_menu)0x8001D6DC)

extern void sf_fn_sfx_play(s64 id, float* pos, s32 token);
