#include "map.h"
#include "save.h"
#include "util.h"
#include "main.h"
#include "ap/ap.h"
#include "sf/map.h"
#include "sf/gfx.h"
#include "sf/game.h"
#include "sf/controller.h"
#include <stdlib.h>

map_t map = {0, };

ap_location_t map_get_clear_location(sf_planet_id_t planet, u8 mission_status) {
  const ap_location_t locations[][3] = {
    {AP_LOCATION_METEO_MISSION_COMPLETE, AP_LOCATION_NONE, AP_LOCATION_METEO_WARP},
    {AP_LOCATION_AREA_6_MISSION_COMPLETE, AP_LOCATION_NONE, AP_LOCATION_NONE},
    {AP_LOCATION_BOLSE_MISSION_COMPLETE, AP_LOCATION_NONE, AP_LOCATION_NONE},
    {AP_LOCATION_SECTOR_Z_MISSION_COMPLETE, AP_LOCATION_SECTOR_Z_MISSION_ACCOMPLISHED, AP_LOCATION_NONE},
    {AP_LOCATION_SECTOR_X_MISSION_COMPLETE, AP_LOCATION_SECTOR_X_MISSION_ACCOMPLISHED, AP_LOCATION_SECTOR_X_WARP},
    {AP_LOCATION_SECTOR_Y_MISSION_COMPLETE, AP_LOCATION_SECTOR_Y_MISSION_ACCOMPLISHED, AP_LOCATION_NONE},
    {AP_LOCATION_KATINA_MISSION_COMPLETE, AP_LOCATION_KATINA_MISSION_ACCOMPLISHED, AP_LOCATION_NONE},
    {AP_LOCATION_MACBETH_MISSION_COMPLETE, AP_LOCATION_MACBETH_MISSION_ACCOMPLISHED, AP_LOCATION_NONE},
    {AP_LOCATION_ZONESS_MISSION_COMPLETE, AP_LOCATION_ZONESS_MISSION_ACCOMPLISHED, AP_LOCATION_NONE},
    {AP_LOCATION_CORNERIA_MISSION_COMPLETE, AP_LOCATION_CORNERIA_MISSION_ACCOMPLISHED, AP_LOCATION_NONE},
    {AP_LOCATION_TITANIA_MISSION_COMPLETE, AP_LOCATION_NONE, AP_LOCATION_NONE},
    {AP_LOCATION_AQUAS_MISSION_COMPLETE, AP_LOCATION_NONE, AP_LOCATION_NONE},
    {AP_LOCATION_FORTUNA_MISSION_COMPLETE, AP_LOCATION_FORTUNA_MISSION_ACCOMPLISHED, AP_LOCATION_NONE},
    {AP_LOCATION_NONE, AP_LOCATION_NONE, AP_LOCATION_NONE},
    {AP_LOCATION_SOLAR_MISSION_COMPLETE, AP_LOCATION_NONE, AP_LOCATION_NONE},
  };
  return locations[planet][mission_status];
}

ap_item_t map_path_item(sf_planet_id_t from, sf_planet_id_t to) {
  const ap_item_t paths[] = {
    AP_ITEM_CORNERIABLUEPATH,
    AP_ITEM_METEOBLUEPATH,
    AP_ITEM_FORTUNABLUEPATH,
    AP_ITEM_SECTORXBLUEPATH,
    AP_ITEM_TITANIABLUEPATH,
    AP_ITEM_KATINABLUEPATH,
    AP_ITEM_MACBETHBLUEPATH,
    AP_ITEM_SECTORZBLUEPATH,
    AP_ITEM_BOLSEBLUEPATH,
    AP_ITEM_SECTORYYELLOWPATH,
    AP_ITEM_KATINAYELLOWPATH,
    AP_ITEM_SOLARYELLOWPATH,
    AP_ITEM_SECTORXYELLOWPATH,
    AP_ITEM_FORTUNAYELLOWPATH,
    AP_ITEM_ZONESSYELLOWPATH,
    AP_ITEM_CORNERIAREDPATH,
    AP_ITEM_SECTORYREDPATH,
    AP_ITEM_AQUASREDPATH,
    AP_ITEM_ZONESSREDPATH,
    AP_ITEM_SECTORZREDPATH,
    AP_ITEM_MACBETHREDPATH,
    AP_ITEM_AREA6REDPATH,
    AP_ITEM_METEOWARPPATH,
    AP_ITEM_SECTORXWARPPATH,
  };
  for (int i = 0; i < 24; i++) {
    sf_path_t path = sf_map_paths[i];
    if (path.start == from && path.end == to) return paths[i];
  }
  return AP_ITEM_NONE;
}

void map_give_clear_location(sf_planet_id_t planet, u8 mission_status) {
  ap_location_t location = map_get_clear_location(planet, mission_status);
  if (location >= 0) {
    set_bit(ap_save.locations, location);
    if (!ap_save.options[AP_OPTION_SHUFFLE_PATHS]) {
      ap_item_t item = map_path_item(planet, sf_map_planets[planet].dests[mission_status]);
      if (item != AP_ITEM_NONE) ap_save.items[item] = 1;
    }
  }
}

int map_set_level_flags(sf_level_t level, sf_level_flag_t flag) {
  if (map.ignore_rewards) {
    map.ignore_rewards = false;
    return 0;
  }
  ap_location_t location;
  switch (flag) {
    case LEVEL_FLAG_CLEAR:
      map_give_clear_location(sf_map_current_planet, sf_map_mission_status);
      if (ap_save.options[AP_OPTION_ACCOMPLISHED_SENDS_COMPLETE] && sf_map_mission_status == MISSION_ACCOMPLISHED) {
        map_give_clear_location(sf_map_current_planet, MISSION_COMPLETE);
      }
      if (sf_map_current_planet == PLANET_VENOM) {
        if (sf_map_venom_hard_clear) set_bit(ap_save.locations, AP_LOCATION_VENOM_DEFEAT_ANDROSS);
        else set_bit(ap_save.locations, AP_LOCATION_VENOM_DEFEAT_ROBOT_ANDROSS);
        bool andross = get_bit(ap_save.locations, AP_LOCATION_VENOM_DEFEAT_ANDROSS);
        bool robot_andross = get_bit(ap_save.locations, AP_LOCATION_VENOM_DEFEAT_ROBOT_ANDROSS);
        switch (ap_save.options[AP_OPTION_VICTORY_CONDITION]) {
          case AP_OPTION_VICTORY_CONDITION_ANDROSS:
            if (andross) main_goal_completed();
            break;
          case AP_OPTION_VICTORY_CONDITION_ANDROSS_AND_ROBOT_ANDROSS:
            if (andross && robot_andross) main_goal_completed();
            break;
          case AP_OPTION_VICTORY_CONDITION_ANDROSS_OR_ROBOT_ANDROSS:
            if (andross || robot_andross) main_goal_completed();
            break;
        }
      }
      break;
    case LEVEL_FLAG_MEDAL:
      switch (level) {
        case LEVEL_AQUAS:
          location = AP_LOCATION_AQUAS_MEDAL;
          break;
        case LEVEL_AREA_6:
          location = AP_LOCATION_AREA_6_MEDAL;
          break;
        case LEVEL_BOLSE:
          location = AP_LOCATION_BOLSE_MEDAL;
          break;
        case LEVEL_CORNERIA:
          location = AP_LOCATION_CORNERIA_MEDAL;
          break;
        case LEVEL_FORTUNA:
          location = AP_LOCATION_FORTUNA_MEDAL;
          break;
        case LEVEL_KATINA:
          location = AP_LOCATION_KATINA_MEDAL;
          break;
        case LEVEL_MACBETH:
          location = AP_LOCATION_MACBETH_MEDAL;
          break;
        case LEVEL_METEO:
          location = AP_LOCATION_METEO_MEDAL;
          break;
        case LEVEL_SECTOR_X:
          location = AP_LOCATION_SECTOR_X_MEDAL;
          break;
        case LEVEL_SECTOR_Y:
          location = AP_LOCATION_SECTOR_Y_MEDAL;
          break;
        case LEVEL_SECTOR_Z:
          location = AP_LOCATION_SECTOR_Z_MEDAL;
          break;
        case LEVEL_SOLAR:
          location = AP_LOCATION_SOLAR_MEDAL;
          break;
        case LEVEL_TITANIA:
          location = AP_LOCATION_TITANIA_MEDAL;
          break;
        case LEVEL_VENOM_1:
        case LEVEL_VENOM_2:
          location = AP_LOCATION_VENOM_MEDAL;
          break;
        case LEVEL_ZONESS:
          location = AP_LOCATION_ZONESS_MEDAL;
          break;
        default:
          location = -1;
      }
      if (location >= 0) set_bit(ap_save.locations, location);
      if (!ap_save.options[AP_OPTION_SHUFFLE_MEDALS]) ap_save.items[AP_ITEM_MEDAL]++;
      break;
  }
  return sf_fn_set_level_flag(level, flag);
}

extern void map_camera_animations_displaced();
void map_camera_animations() {
  if (sf_map_counter == 30) {
    sf_map_counter++;
    sf_map_state = 3;
    sf_map_no_menu = true;
    for (int i = 3; i < 6; i++) {
      sf_map_camera_pos[i] = sf_map_camera_pos[0];
      sf_map_camera_look[i] = sf_map_camera_look[0];
    }
  }
  map_camera_animations_displaced();
}

bool map_has_path(sf_planet_id_t from, sf_planet_id_t to) {
  if (ap_save.items[AP_ITEM_MEDAL] < ap_save.options[AP_OPTION_REQUIRED_MEDALS] && to == PLANET_VENOM) {
    switch (ap_save.options[AP_OPTION_VICTORY_CONDITION]) {
      case AP_OPTION_VICTORY_CONDITION_ANDROSS:
      case AP_OPTION_VICTORY_CONDITION_ANDROSS_AND_ROBOT_ANDROSS:
        if (from == PLANET_AREA_6) return false;
        break;
      case AP_OPTION_VICTORY_CONDITION_ANDROSS_OR_ROBOT_ANDROSS:
        return false;
    }
  }
  ap_item_t path = map_path_item(from, to);
  return path == AP_ITEM_NONE ? false : ap_save.items[path];
}

void map_check_paths(sf_planet_id_t from, bool* planet_access) {
  if (planet_access[from]) return;
  planet_access[from] = true;
  for (int i = 0; i < 3; i++) {
    sf_planet_id_t to = sf_map_planets[from].dests[i];
    if (map_has_path(from, to)) map_check_paths(to, planet_access);
  }
}

void map_paths() {
  bool planet_access[PLANET_MAX] = {0, };
  map_check_paths(PLANET_CORNERIA, planet_access);
  for (int i = 0; i < 24; i++) {
    sf_path_t* path = &sf_map_paths[i];
    u32* path_type = &sf_map_path_types[i];
    bool has_location = false;
    if (planet_access[path->start]) {
      ap_location_t location = AP_LOCATION_NONE;
      for (int i = 0; i < 3; i++) {
        if (sf_map_planets[path->start].dests[i] == path->end) location = map_get_clear_location(path->start, i);
      }
      if (location != AP_LOCATION_NONE) has_location = get_bit(ap_save.locations, location);
    }
    bool has_path = map_has_path(path->start, path->end);
    if (has_path) path->alpha = 0x0F;
    else if (planet_access[path->start]) path->alpha = 0xFF;
    else path->alpha = 0;
    if (has_path) *path_type = 3;
    else *path_type = 4;
    if (!planet_access[path->start]) path->ship = 0;
    else if (has_location) path->ship = 1;
    else path->ship = 2;
  }
  sf_planet_id_t last = PLANET_CORNERIA;
  for (int i = 1; i <= sf_map_current_mission; i++) {
    sf_planet_id_t next = sf_map_mission_list[i];
    for (int i = 0; i < 24; i++) {
      if (sf_map_paths[i].start == last && sf_map_paths[i].end == next) {
        sf_map_paths[i].alpha = 0xFF;
        last = next;
        break;
      }
    }
  }
  sf_total_hits = 0;
  for (int i = 0; i < sf_map_current_mission; i++) sf_total_hits += sf_mission_hits[i];
}

void map_check_mission() {
  switch (sf_map_level_id) {
    case LEVEL_VENOM_1:
    case LEVEL_VENOM_2:
      sf_map_level_start_state = 2; // skip to after briefing
      util_inject(UTIL_INJECT_RETURN, 0x801A2304, 1, 0); // skip pepper init
      util_inject(UTIL_INJECT_JUMP, 0x801A9C2C, 0x801A9DC8, 1); // hide mission text
      break;
    case LEVEL_CORNERIA:
      for (int i = 0; i < 6; i++) {
        sf_team_shields[i] = 0xFF;
        sf_saved_team_shields[i] = 0xFF;
      }
      break;
  }
}

void map_modify() {
  sf_map_previous_planet = sf_map_mission_list[sf_map_current_mission-1];
  sf_map_current_planet = sf_map_mission_list[sf_map_current_mission];
  sf_map_next_planet = sf_map_mission_list[sf_map_current_mission];
  sf_map_planets[PLANET_BOLSE].dest.complete = PLANET_VENOM;
  sf_map_planets[PLANET_AREA_6].dest.complete = PLANET_VENOM;
  util_inject(UTIL_INJECT_JUMP, 0x801A6620, (u32)map_check_mission, 0);
  for (int i = 0; i < 24; i++) {
    sf_map_path_types[i] = 0;
    sf_map_paths[i].ship = 0;
    switch (sf_map_paths[i].color) {
      case PL_WARP_RED:
        sf_map_paths[i].color = PL_PATH_RED;
        break;
      case PL_WARP_YLW:
        sf_map_paths[i].color = PL_PATH_YLW;
        break;
    }
  }
  map_paths();
}

void map_set_mission() {
  sf_map_current_planet = sf_map_previous_planet;
  sf_map_next_planet = sf_map_previous_planet;
}

void map_init() {
  sf_map_no_menu = true;
  sf_map_last_state = 7;
  save_sync_medals();
}

void map_idle() {
  if (!map.inited) {
    map.inited = true;
    save.dirty = true;
    map_modify();
    save_sync_medals();
    sf_map_ship_anim_state = 10;
    sf_controller_timeout = 0;
    if (sf_map_previous_planet == PLANET_AREA_6) sf_map_level_id = LEVEL_VENOM_2;
    if (sf_team_shields[TEAM_ID_SLIPPY] == -2) sf_team_shields[TEAM_ID_SLIPPY] = 0;
    if (sf_saved_team_shields[TEAM_ID_SLIPPY] == -2) sf_saved_team_shields[TEAM_ID_SLIPPY] = 0;
  }
  if (map.check) {
    map.check = false;
    map_paths();
    save_sync_medals();
  }
  if (sf_controllers_pressed[0].dright) {
    sf_planet_t planet = sf_map_planets[sf_map_current_planet];
    for (int i = 0; i < 3; i++) {
      sf_planet_id_t dest = planet.dests[i];
      if (dest == PLANET_NONE || !map_has_path(sf_map_current_planet, dest)) continue;
      sf_map_previous_planet = sf_map_current_planet;
      sf_map_current_planet = dest;
      sf_map_next_planet = dest;
      sf_map_current_mission++;
      sf_map_mission_list[sf_map_current_mission] = dest;
      sf_fn_map_set_level_id();
      if (sf_map_previous_planet == PLANET_AREA_6) sf_map_level_id = LEVEL_VENOM_2;
      goto found_planet;
    }
    found_planet:
    map_paths();
  }
  if (sf_controllers_pressed[0].dleft) {
    if (sf_map_current_mission) {
      if (sf_map_current_mission < 6) sf_map_mission_list[sf_map_current_mission] = PLANET_NONE;
      sf_map_current_mission--;
      sf_map_previous_planet = sf_map_mission_list[sf_map_current_mission-1];
      sf_map_current_planet = sf_map_mission_list[sf_map_current_mission];
      sf_map_next_planet = sf_map_mission_list[sf_map_current_mission];
      sf_fn_map_set_level_id();
      map_paths();
    }
  }
  if (sf_map_current_mission > 0 && sf_map_current_mission < 6) {
    sf_planet_t previous_planet = sf_map_planets[sf_map_previous_planet];
    sf_planet_id_t current_planet = sf_map_current_planet;
    sf_planet_id_t dest = PLANET_NONE;
    if (sf_controllers_pressed[0].dup) {
      sf_planet_id_t dests[3] = {
        previous_planet.dest.warp,
        previous_planet.dest.accomplished,
        previous_planet.dest.complete,
      };
      for (int i = 0; i < 3; i++) {
        if (dests[i] == current_planet) break;
        if (dests[i] == PLANET_NONE || !map_has_path(sf_map_previous_planet, dests[i])) continue;
        dest = dests[i];
      }
    }
    if (sf_controllers_pressed[0].ddown) {
      sf_planet_id_t dests[3] = {
        previous_planet.dest.complete,
        previous_planet.dest.accomplished,
        previous_planet.dest.warp,
      };
      for (int i = 0; i < 3; i++) {
        if (dests[i] == current_planet) break;
        if (dests[i] == PLANET_NONE || !map_has_path(sf_map_previous_planet, dests[i])) continue;
        dest = dests[i];
      }
    }
    if (dest != PLANET_NONE) {
      sf_map_current_planet = dest;
      sf_map_next_planet = dest;
      sf_map_mission_list[sf_map_current_mission] = dest;
      sf_fn_map_set_level_id();
      map_paths();
    }
  }
  sf_fn_map_idle();
}

void map_draw_medals() {
  if (sf_current_scene != SCENE_MAP) return;
  int num[2] = {ap_save.items[AP_ITEM_MEDAL], ap_save.options[AP_OPTION_REQUIRED_MEDALS]};
  if (!ap_save.options[AP_OPTION_SHUFFLE_MEDALS] && !num[1]) return;
  char medals[6];
  for (int i = 0; i < 2; i++) {
    if (num[i] < 99) itoa(num[i], medals+i*3, 10);
  }
  if (medals[1] == 0) {
    medals[1] = medals[0];
    medals[0] = ' ';
  }
  if (num[1]) medals[2] = ':';
  else medals[2] = 0;
  sf_fn_gfx_draw_medal(39.25, 25.75, 0);
  sf_fn_gfx_setup(&sf_gfx, 0x53);
  sf_fn_gfx_color(0xFF, 0xFF, 0, 0xFF);
  sf_fn_gfx_draw_text(268, 38, 1, 1, medals);
}

void map_load_scene_data() {
  map.inited = false;
  util_inject(UTIL_INJECT_FUNCTION, 0x8019F278, (u32)map_set_level_flags, 0); // clear
  util_inject(UTIL_INJECT_FUNCTION, 0x8019F2C0, (u32)map_set_level_flags, 0); // medal
  util_inject(UTIL_INJECT_FUNCTION, 0x8019F2E8, (u32)map_set_mission, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x8019F2F0, 0x8019F39C, 1);
  util_inject(UTIL_INJECT_RAW     , 0x8019F3A0, 0, 0);
  util_inject(UTIL_INJECT_JUMP    , 0x8019F834, (u32)map_init, 0);
  util_inject(UTIL_INJECT_FUNCTION, 0x801A0000, (u32)map_idle, 0);
  util_inject(UTIL_INJECT_JUMP    , 0x801A2AF8, 0x801A2B7C, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x801A2EB8, (u32)map_camera_animations, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x801AB174, (u32)map_draw_medals, 0);
}
