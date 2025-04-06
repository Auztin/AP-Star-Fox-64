#pragma once

#include "n64/types.h"

#define	SF_GFX_SET_PRIMARY_COLOR  0xFA

typedef union {
  struct {
    u8 cmd;
    u8 _unused;
    u8 m;
    u8 l;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
  };
  u64 raw;
} sf_gfx_t;

#define sf_gfx (*(sf_gfx_t**)0x80137E64)
#define sf_fn_gfx_color(red, green, blue, alpha) ({                                                                         \
  sf_gfx->raw = (sf_gfx_t){.cmd=SF_GFX_SET_PRIMARY_COLOR, ._unused=0, .m=0, .l=0, .r=red, .g=green, .b=blue, .a=alpha}.raw; \
  sf_gfx++;                                                                                                                 \
})

typedef int (*sf_fnt_gfx_setup)(sf_gfx_t**, u64 id);
#define sf_fn_gfx_setup ((sf_fnt_gfx_setup)0x800B8DD0)

extern void sf_fn_gfx_draw_medal(float x, float y, float z);
extern void sf_fn_gfx_draw_text(s32 x, s32 y, float xScale, float yScale, char* text);
