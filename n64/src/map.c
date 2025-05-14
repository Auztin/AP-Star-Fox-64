#include "map.h"
#include "save.h"
#include "util.h"
#include "main.h"
#include "ap/ap.h"
#include "sf/map.h"
#include "sf/gfx.h"
#include "sf/sfx.h"
#include "sf/game.h"
#include "sf/controller.h"
#include <stdlib.h>
#include <string.h>

map_t map = {0, };

ap_location_t map_get_clear_location(sf_planet_id_t planet, u8 mission_status) {
  static const ap_location_t locations[][3] = {
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
  static const ap_item_t paths[] = {
    AP_ITEM_CORNERIA_BLUE_PATH,
    AP_ITEM_METEO_BLUE_PATH,
    AP_ITEM_FORTUNA_BLUE_PATH,
    AP_ITEM_SECTOR_X_BLUE_PATH,
    AP_ITEM_TITANIA_BLUE_PATH,
    AP_ITEM_KATINA_BLUE_PATH,
    AP_ITEM_MACBETH_BLUE_PATH,
    AP_ITEM_SECTOR_Z_BLUE_PATH,
    AP_ITEM_BOLSE_BLUE_PATH,
    AP_ITEM_SECTOR_Y_YELLOW_PATH,
    AP_ITEM_KATINA_YELLOW_PATH,
    AP_ITEM_SOLAR_YELLOW_PATH,
    AP_ITEM_SECTOR_X_YELLOW_PATH,
    AP_ITEM_FORTUNA_YELLOW_PATH,
    AP_ITEM_ZONESS_YELLOW_PATH,
    AP_ITEM_CORNERIA_RED_PATH,
    AP_ITEM_SECTOR_Y_RED_PATH,
    AP_ITEM_AQUAS_RED_PATH,
    AP_ITEM_ZONESS_RED_PATH,
    AP_ITEM_SECTOR_Z_RED_PATH,
    AP_ITEM_MACBETH_RED_PATH,
    AP_ITEM_AREA_6_RED_PATH,
    AP_ITEM_METEO_WARP_PATH,
    AP_ITEM_SECTOR_X_WARP_PATH,
  };
  for (int i = 0; i < 24; i++) {
    sf_path_t path = sf_map_paths[i];
    if (path.start == from && path.end == to) return paths[i];
  }
  return AP_ITEM_NONE;
}

void map_give_clear_location(sf_planet_id_t planet, u8 mission_status) {
  ap_location_t location = map_get_clear_location(planet, mission_status);
  if (location != AP_LOCATION_NONE) set_bit(ap_save.locations, location);
}

int map_set_level_flags(sf_level_t level, sf_level_flag_t flag) {
  save_custom_data_planet_t* save_planet = &ap_save.planets[sf_map_current_planet];
  if (flag == LEVEL_FLAG_CLEAR) {
    for (int i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
      if (map.ignore_rewards) {
        switch (sf_map_current_planet) {
          case PLANET_TITANIA:
          case PLANET_SECTOR_X:
            if (sf_team_shields[i] != -2) break;
          case PLANET_CORNERIA:
          case PLANET_AQUAS:
            sf_team_shields[i] = ap_save.shields.team[i-1];
            break;
        }
      }
      if (sf_team_shields[i] == 0) {
        if (map.ignore_rewards) sf_team_shields[i]--;
        else sf_team_shields[i] = 0xFF;
      }
      if (sf_team_shields[i] == -2) sf_team_shields[i] = 0xFF;
      ap_save.shields.team[i-1] =
      sf_saved_team_shields[i] =
      sf_prev_planet_team_shields[i] =
      sf_prev_planet_saved_team_shields[i] = sf_team_shields[i];
    }
    ap_save.lasers = sf_laser_strength;
    ap_save.gold_rings = sf_gold_rings;
    ap_save.lives = sf_lives;
    ap_save.bombs = sf_bombs;
    ap_save.great_fox_intact = sf_great_fox_intact;
  }
  if (map.ignore_rewards) {
    map.ignore_rewards = false;
    return 0;
  }
  ap_location_t location;
  switch (flag) {
    case LEVEL_FLAG_CLEAR:
      if (sf_team_shields[TEAM_ID_PEPPY] > 0) save_planet->peppy = 1;
      if (sf_team_shields[TEAM_ID_SLIPPY] > 0) save_planet->slippy = 1;
      if (sf_team_shields[TEAM_ID_FALCO] > 0) save_planet->falco = 1;
      if (sf_hits > save_planet->score) save_planet->score = sf_hits;
      if (sf_map_current_planet == PLANET_FORTUNA) {
        ap_save.star_wolf_alive.wolf = sf_star_wolf_alive[TEAM_ID_WOLF];
        ap_save.star_wolf_alive.leon = sf_star_wolf_alive[TEAM_ID_LEON];
        ap_save.star_wolf_alive.pigma = sf_star_wolf_alive[TEAM_ID_PIGMA];
        ap_save.star_wolf_alive.andrew = sf_star_wolf_alive[TEAM_ID_ANDREW];
      }
      map_give_clear_location(sf_map_current_planet, sf_map_mission_status);
      if (ap_save.options[AP_OPTION_ACCOMPLISHED_SENDS_COMPLETE] && sf_map_mission_status == MISSION_ACCOMPLISHED) {
        map_give_clear_location(sf_map_current_planet, MISSION_COMPLETE);
      }
      if (sf_map_current_planet == PLANET_VENOM) {
        sf_mission_clear[LEVEL_VENOM_1] =
        sf_mission_clear[LEVEL_VENOM_2] =
        sf_mission_clear[LEVEL_VENOM_ANDROSS] = main_check_medal(200) + 1;
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
    sf_map_cutscene_state = 3;
    sf_map_no_menu = false;
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
  if (ap_save.options[AP_OPTION_LEVEL_ACCESS] != AP_OPTION_LEVEL_ACCESS_SHUFFLE_PATHS) return true;
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

bool map_has_level_item(sf_level_t level) {
  switch (level) {
    case LEVEL_CORNERIA: return ap_save.items[AP_ITEM_CORNERIA];
    case LEVEL_METEO: return ap_save.items[AP_ITEM_METEO];
    case LEVEL_SECTOR_X: return ap_save.items[AP_ITEM_SECTOR_X];
    case LEVEL_AREA_6: return ap_save.items[AP_ITEM_AREA_6];
    case LEVEL_SECTOR_Y: return ap_save.items[AP_ITEM_SECTOR_Y];
    case LEVEL_VENOM_1: return ap_save.items[AP_ITEM_VENOM];
    case LEVEL_SOLAR: return ap_save.items[AP_ITEM_SOLAR];
    case LEVEL_ZONESS: return ap_save.items[AP_ITEM_ZONESS];
    case LEVEL_VENOM_ANDROSS: return ap_save.items[AP_ITEM_VENOM];
    case LEVEL_MACBETH: return ap_save.items[AP_ITEM_MACBETH];
    case LEVEL_TITANIA: return ap_save.items[AP_ITEM_TITANIA];
    case LEVEL_AQUAS: return ap_save.items[AP_ITEM_AQUAS];
    case LEVEL_FORTUNA: return ap_save.items[AP_ITEM_FORTUNA];
    case LEVEL_KATINA: return ap_save.items[AP_ITEM_KATINA];
    case LEVEL_BOLSE: return ap_save.items[AP_ITEM_BOLSE];
    case LEVEL_SECTOR_Z: return ap_save.items[AP_ITEM_SECTOR_Z];
    case LEVEL_VENOM_2: return ap_save.items[AP_ITEM_VENOM];
    default: return true;
  }
}

void map_paths() {
  static const ap_location_t medal_locations[] = {
    AP_LOCATION_METEO_MEDAL,
    AP_LOCATION_AREA_6_MEDAL,
    AP_LOCATION_BOLSE_MEDAL,
    AP_LOCATION_SECTOR_Z_MEDAL,
    AP_LOCATION_SECTOR_X_MEDAL,
    AP_LOCATION_SECTOR_Y_MEDAL,
    AP_LOCATION_KATINA_MEDAL,
    AP_LOCATION_MACBETH_MEDAL,
    AP_LOCATION_ZONESS_MEDAL,
    AP_LOCATION_CORNERIA_MEDAL,
    AP_LOCATION_TITANIA_MEDAL,
    AP_LOCATION_AQUAS_MEDAL,
    AP_LOCATION_FORTUNA_MEDAL,
    AP_LOCATION_VENOM_MEDAL,
    AP_LOCATION_SOLAR_MEDAL,
  };
  static const sf_level_t planet_to_level[] = {
    LEVEL_METEO,
    LEVEL_AREA_6,
    LEVEL_BOLSE,
    LEVEL_SECTOR_Z,
    LEVEL_SECTOR_X,
    LEVEL_SECTOR_Y,
    LEVEL_KATINA,
    LEVEL_MACBETH,
    LEVEL_ZONESS,
    LEVEL_CORNERIA,
    LEVEL_TITANIA,
    LEVEL_AQUAS,
    LEVEL_FORTUNA,
    LEVEL_VENOM_ANDROSS,
    LEVEL_SOLAR,
  };
  bool planet_access[PLANET_MAX] = {0, };
  ap_option_level_access_t level_access = ap_save.options[AP_OPTION_LEVEL_ACCESS];
  int minimum_path_alpha = 0;
  if (level_access == AP_OPTION_LEVEL_ACCESS_SHUFFLE_PATHS) map_check_paths(PLANET_CORNERIA, planet_access);
  else {
    for (int i = 0; i < PLANET_MAX; i++) planet_access[i] = map_has_level_item(planet_to_level[i]);
    minimum_path_alpha = 0x40;
  }
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
    bool has_path;
    switch (level_access) {
      case AP_OPTION_LEVEL_ACCESS_SHUFFLE_LEVELS:
        has_path = planet_access[path->start];
        break;
      case AP_OPTION_LEVEL_ACCESS_SHUFFLE_PATHS:
        has_path = map_has_path(path->start, path->end);
        break;
    }
    if (has_path) path->alpha = 0x0F;
    else if (planet_access[path->start]) path->alpha = 0xFF;
    else path->alpha = minimum_path_alpha;
    if (has_path) *path_type = 3;
    else *path_type = 4;
    if (!planet_access[path->start]) path->ship = 0;
    else if (has_location) path->ship = 1;
    else path->ship = 2;
  }
  sf_planet_id_t last = PLANET_CORNERIA;
  sf_total_hits = 0;
  memset(sf_mission_clear, 0, 30);
  for (int i = 0; i < 7; i++) {
    sf_planet_id_t next = sf_map_mission_list[i];
    save_custom_data_planet_t* save_planet = &ap_save.planets[next];
    sf_mission_hits[i] = save_planet->score;
    if (next > PLANET_NONE && next < PLANET_MAX) sf_mission_medals[i] = get_bit(ap_save.locations, medal_locations[next]);
    sf_mission_team[i].peppy = save_planet->peppy ? 0xFF : 0;
    sf_mission_team[i].slippy = save_planet->slippy ? 0xFF : 0;
    sf_mission_team[i].falco = save_planet->falco ? 0xFF : 0;
    if (i < sf_map_current_mission) {
      sf_total_hits += sf_mission_hits[i];
      if (level_access != AP_OPTION_LEVEL_ACCESS_SHUFFLE_LEVELS || planet_access[next]) {
        sf_mission_clear[planet_to_level[next]] = sf_mission_medals[i] + 1;
      }
    }
    if (i && i <= sf_map_current_mission) {
      for (int i = 0; i < 24; i++) {
        if (sf_map_paths[i].start == last && sf_map_paths[i].end == next) {
          sf_map_paths[i].alpha = 0xFF;
          last = next;
          break;
        }
      }
    }
  }
}

void map_check_mission() {
  sf_gold_rings = sf_saved_gold_rings = ap_save.gold_rings;
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
    case LEVEL_BOLSE:
      for (int i = TEAM_ID_WOLF; i <= TEAM_ID_ANDREW; i++) sf_star_wolf_alive[i] = 1;
      for (int i = 0; i < 7; i++) {
        if (sf_map_mission_list[i] == PLANET_FORTUNA) {
          sf_star_wolf_alive[TEAM_ID_WOLF] = ap_save.star_wolf_alive.wolf;
          sf_star_wolf_alive[TEAM_ID_LEON] = ap_save.star_wolf_alive.leon;
          sf_star_wolf_alive[TEAM_ID_PIGMA] = ap_save.star_wolf_alive.pigma;
          sf_star_wolf_alive[TEAM_ID_ANDREW] = ap_save.star_wolf_alive.andrew;
          break;
        }
      }
      for (int i = TEAM_ID_WOLF; i <= TEAM_ID_ANDREW; i++) sf_saved_star_wolf_alive[i] = sf_star_wolf_alive[i];
      break;
  }
}

void map_check_level_access() {
  if (
    ap_save.options[AP_OPTION_LEVEL_ACCESS] != AP_OPTION_LEVEL_ACCESS_SHUFFLE_LEVELS
    || map_has_level_item(sf_map_level_id)
  ) sf_fn_map_select_level();
  else sf_fn_sfx_play(SF_SFX_ERROR, sf_sfx_default_pos, 4);
}

void map_modify() {
  sf_map_previous_planet = sf_map_mission_list[sf_map_current_mission-1];
  sf_map_current_planet = sf_map_mission_list[sf_map_current_mission];
  sf_map_next_planet = sf_map_mission_list[sf_map_current_mission];
  sf_map_planets[PLANET_BOLSE].dest.complete = PLANET_VENOM;
  sf_map_planets[PLANET_AREA_6].dest.complete = PLANET_VENOM;
  util_inject(UTIL_INJECT_JUMP    , 0x801A6620, (u32)map_check_mission, 0);
  util_inject(UTIL_INJECT_FUNCTION, 0x801AD228, (u32)map_check_level_access, 0);
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
  sf_map_no_menu = false;
  sf_map_last_state = 7;
  sf_reset_flags = false;
  for (int i = TEAM_ID_FALCO; i < TEAM_ID_MAX; i++) {
    sf_team_shields[i] =
    sf_saved_team_shields[i] =
    sf_prev_planet_team_shields[i] =
    sf_prev_planet_saved_team_shields[i] = i <= TEAM_ID_PEPPY ? ap_save.shields.team[i-1] : 0xFF;
  }
  for (int i = 0; i < 6; i++) {
    sf_star_wolf_alive[i] =
    sf_saved_star_wolf_alive[i] = true;
  }
  sf_laser_strength = ap_save.lasers;
  sf_gold_rings = sf_saved_gold_rings = ap_save.gold_rings;
  sf_total_hits = 0;
  sf_lives = ap_save.lives == -1 ? ap_save.options[AP_OPTION_DEFAULT_LIVES] : ap_save.lives;
  sf_bombs = ap_save.bombs;
  sf_great_fox_intact = ap_save.great_fox_intact;
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
    sf_hits = 0;
    if (sf_map_previous_planet == PLANET_AREA_6) sf_map_level_id = LEVEL_VENOM_2;
  }
  if (map.check) {
    map.check = false;
    map_paths();
    save_sync_medals();
  }
  if (sf_controllers_pressed[0].b) {
    sf_last_state = GSTATE_INIT;
    sf_next_state = GSTATE_MENU;
    sf_option_menu_status = 0;
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
  if (ap_save.items[AP_ITEM_EXTRA_ARWING] > ap_save.received.lives) {
    sf_lives += ap_save.items[AP_ITEM_EXTRA_ARWING]-ap_save.received.lives;
    if (sf_lives > 99) sf_lives = 99;
  }
  ap_save.received.lives = ap_save.items[AP_ITEM_EXTRA_ARWING];
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

void map_load_scene_data(sf_scenes_t scene) {
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
  util_inject(UTIL_INJECT_JUMP    , 0x801AD170, 0x801AD1D0, 0);
  if (scene == SCENE_GAME_OVER) {
    for (int i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) ap_save.shields.team[i-1] = 0xFF;
    ap_save.lasers = LASERS_SINGLE;
    ap_save.gold_rings = 0;
    ap_save.lives = -1;
    ap_save.bombs = 3;
  }
}
