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

.align 0x08
sf_fn_play_radio_message:
ADDIU SP, SP, -0x28
SW RA, 0x0014 (SP)
JAL 0x800BA810
NOP

.align 0x08
main_menu_selected_displaced:
LHU V0, 0xD898 (V0)
ANDI T2, V0, 0x9000
ADDIU SP, SP, -0x18
SW RA, 0x0000 (SP)
JAL main_menu_selected
SW V0, 0x0004 (SP)
ADDIU T2, V0, 0x0000
LW RA, 0x0000 (SP)
LW V0, 0x0004 (SP)
ADDIU SP, SP, 0x18
JR RA
NOP

.align 0x08
sf_fn_check_medal:
J 0x800A3F58
ANDI T6, A0, 0xFFFF

.align 0x08
sf_fn_gfx_draw_texture:
LD V0, 0x0020 (SP)
SW V0, 0x0010 (SP)
LD V0, 0x0028 (SP)
SW V0, 0x0014 (SP)
LD V0, 0x0030 (SP)
SW V0, 0x0018 (SP)
LD V0, 0x0030 (SP)
SW V0, 0x0018 (SP)
LD V0, 0x0038 (SP)
SW V0, 0x001C (SP)
J 0x8009D994
NOP
