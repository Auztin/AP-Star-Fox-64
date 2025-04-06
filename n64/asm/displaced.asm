.align 0x08
map_camera_animations_displaced:
ADDIU SP, SP, -0x20
J 0x801A2EC0
SW RA, 0x001C (SP)

.align 0x08
main_pre_venom_displaced:
ADDIU SP, SP, -0x18
J 0x8008856C
SW RA, 0x0014 (SP)

.align 0x08
sf_fn_gfx_draw_medal:
MTC1 A0, F12
MTC1 A1, F14
J 0x801AB17C
NOP

.align 0x08
sf_fn_gfx_draw_text:
LD V0, 0x0020 (SP)
SW V0, 0x0010 (SP)
J 0x800A1200
NOP

.align 0x08
sf_fn_sfx_play:
ADDIU SP, SP, -0x18
LUI A3, 0x800C
LUI T8, 0x800C
ADDIU A3, A3, 0x5D34
ADDIU T8, T8, 0x5D3C
SW T8, 0x0014 (SP)
SW RA, 0x0000 (SP)
JAL 0x80019218
SW A3, 0x0010 (SP)
LW RA, 0x0000 (SP)
JR RA
ADDIU SP, SP, 0x18
