#include "hud.h"
#include "map.h"
#include "save.h"
#include "util.h"
#include "ringlink.h"
#include "ap/ap.h"
#include "sf/gfx.h"
#include "sf/sfx.h"
#include "sf/map.h"
#include "sf/game.h"
#include "sf/controller.h"
#include <stdlib.h>
#include <string.h>

s32 hud_selected_color = 0;
s32 hud_map_menu_selection = 0;
s32 hud_map_menu_timer = 0;
s32* hud_selection;

void hud_update_selected_color(s32 timer) {
  hud_selected_color = (timer % 20);
  if (hud_selected_color >= 10) hud_selected_color = 20 - hud_selected_color;
  if ((hud_selected_color = (hud_selected_color * 16) - 1) < 0) hud_selected_color = 0;
}

void hud_pause_draw_selection(char* text, s32 x, s32 y, s32 entry) {
  if (*hud_selection == entry) sf_fn_gfx_color(160, hud_selected_color, hud_selected_color, 255);
  else sf_fn_gfx_color(64, 64, 64, 255);
  sf_fn_gfx_draw_text(x, y, 1, 1, text);
}

void hud_pause_draw_selections() {
  hud_selection = &sf_pause_selection;
  hud_update_selected_color(sf_pause_timer);
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
  sf_controller_t* p1 = &sf_controllers_pressed[0];
  if (p1->b) sf_pause_action = 10;
  if (p1->a) {
    switch (sf_pause_selection) {
      case 0:
        sf_pause_action = 10;
        break;
      case 1:
        sf_pause_action = 2;
        ringlink.state = RINGLINK_STATE_ZERO_OUT;
        break;
      case 2:
        sf_pause_action = 10;
        ap.in.deathlink++;
        break;
      case 3:
        sf_next_state = GSTATE_MAP;
        sf_last_state = GSTATE_PLAY;
        map.ignore_rewards = true;
        ringlink.state = RINGLINK_STATE_ZERO_OUT;
        break;
    }
  }
}

void hud_map_menu_update() {
  sf_active_controller_pressed = sf_controllers_pressed;
  hud_map_menu_timer++;
  hud_selection = &hud_map_menu_selection;
  hud_update_selected_color(hud_map_menu_timer);
  switch (sf_fn_pause_check_joystick()) {
    case -1:
      hud_map_menu_selection++;
      break;
    case 1:
      hud_map_menu_selection--;
      break;
    default:
      goto after_joystick;
  }
  hud_map_menu_timer = 0;
  switch (hud_map_menu_selection) {
    case -1:
      hud_map_menu_selection = 0;
      break;
    case 3:
      hud_map_menu_selection = 2;
      break;
    default:
      sf_fn_sfx_play(SF_SFX_CURSOR, sf_sfx_default_pos, 4);
  }
  after_joystick:
  sf_controller_t* p1 = &sf_controllers_pressed[0];
  if (p1->b || p1->start) {
    sf_fn_sfx_map_menu(0);
    sf_map_show_menu = 0;
    sf_map_state = 3;
    sf_active_controller_pressed = 0;
  }
  if (p1->a) {
    int team_id = 0;
    switch (hud_map_menu_selection) {
      case 0:
        team_id = TEAM_ID_PEPPY;
        break;
      case 1:
        team_id = TEAM_ID_SLIPPY;
        break;
      case 2:
        team_id = TEAM_ID_FALCO;
        break;
    }
    if (team_id) {
      s32* shields = &sf_team_shields[team_id];
      if (sf_lives && *shields < 0xFF) {
        sf_fn_sfx_play(SF_SFX_DECIDE, sf_sfx_default_pos, 4);
        if (*shields < 0) *shields = 0;
        *shields += 128;
        if (*shields > 0xFF) *shields = 0xFF;
        ap_save.shields.team[team_id-1] =
        sf_saved_team_shields[team_id] =
        sf_prev_planet_team_shields[team_id] =
        sf_prev_planet_saved_team_shields[team_id] = *shields;
        ap_save.lives = --sf_lives;
        save.dirty = true;
      }
      else sf_fn_sfx_play(SF_SFX_ERROR, sf_sfx_default_pos, 4);
    }
  }
}

void hud_map_menu_draw() {
  if (!hud_selection) return;
  sf_fn_gfx_setup(&sf_gfx, 0x4C);
  sf_fn_gfx_color(60, 60, 255, 170);
  int w = 24;
  int h = 17;
  int target_w = 140;
  int target_h = 50;
  int x = 10+SF_GFX_WIDTH/2 - target_w/2;
  int y = 10+SF_GFX_HEIGHT/2 - target_h/2;
  sf_fn_gfx_draw_texture(&sf_gfx, SF_GFXT_MENU_BG, w, h, x, y, target_w/w+0.9, target_h/h+0.9);
  x = 10+SF_GFX_WIDTH/2 - 130/2;
  y = 10+SF_GFX_HEIGHT/2 - 40/2;
  sf_fn_gfx_color(0xFF, 0xFF, 0, 0xFF);
  sf_fn_gfx_draw_text(x, y, 1, 1, "-1 ARWING TO HEAL");
  x = 10+SF_GFX_WIDTH/2 - 122/2;
  char number[4];
  char text[12];
  char* team[] = {
    "PEPPY: ",
    "SLIPPY: ",
    "FALCO: ",
  };
  for (int i = 0; i < 3; i++) {
    s32 shields = sf_team_shields[3-i];
    if (shields > 0) shields = shields/255.0f*100;
    else shields = 0;
    itoa(shields, number, 10);
    strcpy(text, team[i]);
    strcat(text, number);
    hud_pause_draw_selection("HEAL", x, y+=10, i);
    sf_fn_gfx_draw_text(x+(i == 1 ? 40 : 44), y, 1, 1, text);
  }
}

void hud_load_scene_data() {
  util_inject(UTIL_INJECT_FUNCTION, 0x801A0378, (u32)hud_map_menu_draw, 0);
  util_inject(UTIL_INJECT_FUNCTION, 0x801A0084, (u32)hud_map_menu_update, 0);
}
