#include "hud.h"
#include "map.h"
#include "save.h"
#include "ap/ap.h"
#include "sf/gfx.h"
#include "sf/sfx.h"
#include "sf/map.h"
#include "sf/game.h"
#include "sf/controller.h"
#include "hit_count.h"

s32 hud_selected_color = 0;

void hud_pause_draw_selection(char* text, s32 x, s32 y, s32 entry) {
  if (sf_pause_selection == entry) sf_fn_gfx_color(160, hud_selected_color, hud_selected_color, 255);
  else sf_fn_gfx_color(64, 64, 64, 255);
  sf_fn_gfx_draw_text(x, y, 1, 1, text);
}

void hud_pause_draw_selections() {
  hud_selected_color = (sf_pause_timer % 20);
  if (hud_selected_color >= 10) hud_selected_color = 20 - hud_selected_color;
  if ((hud_selected_color = (hud_selected_color * 16) - 1) < 0) hud_selected_color = 0;

  hud_pause_draw_selection("CONTINUE", 128, 96, 0);
  if (sf_map_level_id == LEVEL_TRAINING) hud_pause_draw_selection("QUIT TRAINING", 110, 106, 1);
  else {
    hud_pause_draw_selection("RETRY COURSE", 110, 106, 1);
    hud_pause_draw_selection("RESPAWN", 130, 116, 2);
    hud_pause_draw_selection("BACK TO MAP", 115, 126, 3);
  }
}

void hud_pause_check_input() {
  switch (sf_fn_pause_check_joystick()) {
    case -1:
      sf_pause_selection++;
      break;
    case 1:
      sf_pause_selection--;
      break;
    default:
      goto after_joystick;
  }
  sf_pause_timer = 0;
  switch (sf_pause_selection) {
    case -1:
      sf_pause_selection = 0;
      break;
    case 4:
      sf_pause_selection = 3;
      break;
    default:
      sf_fn_sfx_play(SF_SFX_CURSOR, sf_sfx_default_pos, 4);
  }
  after_joystick:
  if (sf_controllers_pressed[0].b) sf_pause_action = 10;
  if (sf_controllers_pressed[0].a) {
    switch (sf_pause_selection) {
      case 0:
        sf_pause_action = 10;
        break;
      case 1:
        sf_pause_action = 2;
        ringlink_state = RINGLINK_STATE_ZERO_OUT;
        break;
      case 2:
        sf_pause_action = 10;
        ap.received_items[AP_ITEM_DEATH_LINK]++;
        break;
      case 3:
        sf_next_state = GSTATE_MAP;
        sf_last_state = GSTATE_PLAY;
        map.ignore_rewards = true;
        ringlink_state = RINGLINK_STATE_ZERO_OUT;
        break;
    }
  }
}
