#include "main.h"
#include "save.h"
#include "util.h"
#include "usb.h"
#include "map.h"
#include "n64/sys.h"
#include "n64/dma.h"
#include "ap/ap.h"
#include "sf/global.h"
#include "sf/controller.h"
#include "sf/map.h"

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

bool main_load_scene_data(sf_scenes_t scene, u8 _unk) {
  if (scene == SCENE_CREDITS && !get_bit(ap_save.locations, AP_LOCATION_GOAL_COMPLETED)) sf_next_state = GSTATE_MAP;
  bool ret = sf_fn_load_scene_data(scene, _unk);
  if (ret) {
    switch (scene) {
      case SCENE_TITLE:
      case SCENE_MENU:
      case SCENE_MAP:
      case SCENE_GAME_OVER:
        map_load_scene_data(scene);
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
