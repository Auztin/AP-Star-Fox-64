#include "main.h"
#include "save.h"
#include "util.h"
#include "usb.h"
#include "map.h"
#include "hud.h"
#include "n64/sys.h"
#include "n64/dma.h"
#include "ap/ap.h"
#include "ap/states.h"
#include "sf/global.h"
#include "sf/controller.h"
#include "sf/map.h"
#include "sf/sfx.h"
#include "sf/gfx.h"

main_t main = {0, };

void main_init() {
  main.is_emulator = io_read(0xA4100010) == 0 ? 1 : 0;
  if (!main.is_emulator) usb_init();
  ap_init();
  save_init();
}

void main_loop() {
  sf_fn_game_update();
  u32 c0_count = C0_COUNT();
  main.delta = (c0_count-main.last_c0_count)/TICKS_PER_MILLISECOND;
  main.last_c0_count = c0_count;
  if (main.delta >= 250) return;
  if (sf_controllers_held[0].start && sf_controllers_pressed[0].l) {
    if (sf_video_features1 == 0x0001300E) {
      sf_video_features1 = 0x0000320E;
      sf_video_features2 = 0x0000320E;
    }
    else {
      sf_video_features1 = 0x0001300E;
      sf_video_features2 = 0x0001300E;
    }
  }
  save_sram_write();
  if (main.is_emulator) {
    ap_input();
    ap_output();
  }
  else usb_check();
  if (sf_cur_state == GSTATE_PLAY && sf_player) {
    if (ap.in.deathlink) {
      if (sf_player->state == PLAYER_STATE_ACTIVE) {
        sf_player->shields = 0;
        sf_player->radioDamageTimer = 2;
      }
    }
    if (sf_player->state != main.last_player_state) {
      if (sf_player->state == PLAYER_STATE_DOWN) {
        if (ap.in.deathlink) ap.in.deathlink--;
        else ap.out.deathlink++;
      }
      main.last_player_state = sf_player->state;
    }
  }
}

void main_goal_completed() {
  if (!set_bit(ap_save.locations, AP_LOCATION_GOAL_COMPLETED)) sf_next_state = GSTATE_ENDING;
}

extern bool main_menu_selected_displaced();
bool main_menu_selected() {
  s32* selected = (s32*)0x801B91A4;
  sf_controller_t* p1 = &sf_controllers_pressed[0];
  sf_controller_t* h1 = &sf_controllers_held[0];
  if (p1->a || p1->start) {
    switch (*selected) {
      case 0: // Main Game/Expert
      case 1: // Training
        if (ap.ready || (h1->z && h1->r)) return true;
        sf_fn_sfx_play(SF_SFX_ERROR, sf_sfx_default_pos, 4);
        break;
      default:
        return true;
    }
  }
  return false;
}

void main_menu_update() {
  char* text_client = "CLIENT DISCONNECTED";
  char* text_ap = "AP DISCONNECTED";
  if ((ap.state & ~AP_STATE_PINGED) == AP_STATE_CONNECTED) text_client = "CLIENT CONNECTED";
  if (ap.ready) text_ap = "AP CONNECTED";
  sf_fn_main_menu_update();
  sf_fn_gfx_setup(&sf_gfx, 0x53);
  sf_fn_gfx_color(0xFF, 0xFF, 0, 0xFF);
  sf_fn_gfx_draw_text(20, 205, 1, 1, text_client);
  sf_fn_gfx_draw_text(20, 215, 1, 1, text_ap);
}

bool main_check_medal(u16 score) {
  const u16 medals[] = {
    ap_save.options[AP_OPTION_MEDAL_CORNERIA],
    ap_save.options[AP_OPTION_MEDAL_METEO],
    ap_save.options[AP_OPTION_MEDAL_SECTOR_X],
    ap_save.options[AP_OPTION_MEDAL_AREA_6],
    score,
    ap_save.options[AP_OPTION_MEDAL_SECTOR_Y],
    ap_save.options[AP_OPTION_MEDAL_VENOM],
    ap_save.options[AP_OPTION_MEDAL_SOLAR],
    ap_save.options[AP_OPTION_MEDAL_ZONESS],
    ap_save.options[AP_OPTION_MEDAL_VENOM],
    score,
    ap_save.options[AP_OPTION_MEDAL_MACBETH],
    ap_save.options[AP_OPTION_MEDAL_TITANIA],
    ap_save.options[AP_OPTION_MEDAL_AQUAS],
    ap_save.options[AP_OPTION_MEDAL_FORTUNA],
    score,
    ap_save.options[AP_OPTION_MEDAL_KATINA],
    ap_save.options[AP_OPTION_MEDAL_BOLSE],
    ap_save.options[AP_OPTION_MEDAL_SECTOR_Z],
    ap_save.options[AP_OPTION_MEDAL_VENOM],
  };
  if (sf_map_level_id < countof(medals)) score = medals[sf_map_level_id];
  return sf_fn_check_medal(score);
}

bool main_load_scene_data(sf_scenes_t scene, u8 _unk) {
  if (scene == SCENE_CREDITS && !get_bit(ap_save.locations, AP_LOCATION_GOAL_COMPLETED)) sf_next_state = GSTATE_MAP;
  bool ret = sf_fn_load_scene_data(scene, _unk);
  if (ret) {
    switch (scene) {
      case SCENE_TITLE:
      case SCENE_MENU:
      case SCENE_MAP:
      case SCENE_GAME_OVER:
        util_inject(UTIL_INJECT_FUNCTION, 0x80192224, (u32)main_menu_update, 0);
        util_inject(UTIL_INJECT_FUNCTION, 0x801933E4, (u32)main_menu_selected_displaced, 1);
        map_load_scene_data(scene);
        hud_load_scene_data(scene);
        break;
    }
  }
  return ret;
}

extern void main_pre_venom_displaced();
void main_pre_venom() {
  sf_next_state = GSTATE_MAP;
  sf_map_current_mission--;
  main_pre_venom_displaced();
}
