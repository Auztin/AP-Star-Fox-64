#pragma once

#include "n64/types.h"

#define SF_GFXT_MENU_BG           0x0601B4B0

#define SF_GFX_WIDTH              300
#define SF_GFX_HEIGHT             220
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
  struct {
    u32 w1;
    u32 w2;
  };
  struct {
    u16 h1;
    u16 h2;
    u16 h3;
    u16 h4;
  };
  struct {
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    u8 b8;
  };
  u64 raw;
} sf_display_list_t;

#define sf_gfx (*(sf_display_list_t**)0x80137E64)
#define sf_segment (*(sf_display_list_t**)0x80137E60)
#define sf_fn_gfx_color(red, green, blue, alpha) ({                                                                         \
  sf_gfx->raw = (sf_display_list_t){.cmd=SF_GFX_SET_PRIMARY_COLOR, ._unused=0, .m=0, .l=0, .r=red, .g=green, .b=blue, .a=alpha}.raw; \
  sf_gfx++;                                                                                                                 \
})
#define sf_fn_gfx_env_color(red, green, blue, alpha) ({                                                                         \
  sf_gfx->raw = (sf_display_list_t){.cmd=0xFB, ._unused=0, .m=0, .l=0, .r=red, .g=green, .b=blue, .a=alpha}.raw; \
  sf_gfx++;                                                                                                                 \
})
#define sf_segment_load(index, address) ({      \
  sf_segment->h1 = 0xBC00;                      \
  sf_segment->b3 = index * 4;                   \
  sf_segment->b4 = 6;                           \
  sf_segment->w2 = (u32)(&address) & 0xFFFFFF;  \
  sf_segment++;                                 \
})

typedef int (*sf_fnt_gfx_setup)(sf_display_list_t**, u64 id);
#define sf_fn_gfx_setup ((sf_fnt_gfx_setup)0x800B8DD0)

void sf_fn_gfx_set_scale(float scale);

extern void sf_fn_gfx_draw_medal(float x, float y, float z);
extern void sf_fn_gfx_draw_text(s32 x, s32 y, float xScale, float yScale, char* text);
extern void sf_fn_gfx_draw_texture(sf_display_list_t**, u32 texture, u32 width, u32 height, float xPos, float yPos, float xScale, float yScale);
