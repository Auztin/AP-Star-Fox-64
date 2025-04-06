#pragma once

#define SF_SFX_CURSOR 0x49000002

#define sf_sfx_default_pos ((float*)0x800C5D28)

extern void sf_fn_sfx_play(s64 id, float* pos, s32 token);
