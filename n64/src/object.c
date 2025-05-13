#include "object.h"
#include "save.h"
#include "util.h"
#include "ap/ap.h"
#include "sf/gfx.h"
#include "sf/sfx.h"
#include "sf/map.h"
#include "sf/game.h"

object_t object = {.id=-1, 0, };

ap_location_t object_get_ap_location(sf_level_t level, s16 index);

void object_item_init(sf_item_t* item) {
  sf_fn_object_item_init(item);
  object.last_item = item;
}

void object_item_load(sf_item_t* item, sf_object_init_t* init) {
  object.id = sf_level_objects_index;
  sf_fn_item_load(item, init);
  object.id = -1;
  ap_item_t ap_item = ap_location_item(object.last_ap_id);
  ap_location_group_t ap_group = ap_location_group(object.last_ap_id);
  if (
    ap_save.options[AP_OPTION_SHUFFLE_CHECKPOINTS]
    && ap_group == AP_LOCATION_GROUP_CHECKPOINTS
    && !ap_save.items[ap_item]
    && get_bit(ap_save.locations, object.last_ap_id)
  ) item->status = 0;
}

void object_info(sf_object_info_t* info, u32 id) {
  ap_location_t ap_id = object.last_ap_id = 0;
  if (object.id == -1) ap_id = -sf_level_objects_index;
  else if (info == &object.last_item->info) {
    ap_id = object.last_ap_id = object_get_ap_location(sf_map_level_id, object.id);
    ap_location_group_t ap_group = ap_location_group(ap_id);
    if (
      (ap_id == AP_LOCATION_NONE || get_bit(ap_save.locations, ap_id))
      || (ap_group == AP_LOCATION_GROUP_CHECKPOINTS && !ap_save.options[AP_OPTION_SHUFFLE_CHECKPOINTS])
    ) ap_id = 0;
    else {
      id = OBJ_ITEM_SILVER_RING;
      object.last_item->id = id;
    }
  }
  sf_fn_object_info(info, id);
  info->ap_id = ap_id;
}

void object_item_drop(sf_actor_t* actor) {
  object.id = -actor->info.object_index;
  sf_fn_item_drop(actor);
  object.id = -1;
}

void object_draw_silver_ring(sf_item_t* item) {
  if (item->info.ap_id <= 0) return sf_fn_item_draw_silver_ring(item);
  sf_fn_gfx_color(0xff, 0xff, 0xff, 0xff);
  sf_fn_gfx_set_scale(item->scale);
  sf_fn_gfx_setup(&sf_gfx, 0x1D);
  sf_gfx->w1 = 0x06000000;
  sf_gfx->w2 = ASSET_AP_LOGO;
  sf_gfx++;
}

void object_collect_silver_ring(sf_item_t* item) {
  if (item->info.ap_id > 0 && item->info.ap_id < AP_LOCATION_MAX) {
    sf_fn_sfx_play(SF_SFX_GET_EMBLEM, sf_player->sfx_source, 0);
    set_bit(ap_save.locations, item->info.ap_id);
  }
  else {
    sf_fn_sfx_play(SF_SFX_RING, sf_player->sfx_source, 0);
    sf_player->heal += 32;
  }
}

ap_location_t object_get_ap_location(sf_level_t level, s16 index) {
  switch (level) {
    case LEVEL_CORNERIA:
      switch (index) {
        case 0x005E: return AP_LOCATION_CORNERIA_UNDER_ARCH_GOLD_RING;
        case 0x006C: return AP_LOCATION_CORNERIA_BEHIND_DOORS_BOMB;
        case 0x00A6: return AP_LOCATION_CORNERIA_CENTER_OF_CORNERIA_CITY_SILVER_RING;
        case 0x00DC: return AP_LOCATION_CORNERIA_NEAR_FIRST_GROUND_ROBOT_LASER_UPGRADE;
        case 0x00F0: return AP_LOCATION_CORNERIA_UNDER_HIGHWAY_ARCH_GOLD_RING;
        case 0x011E: return AP_LOCATION_CORNERIA_BEHIND_SECOND_GROUND_ROBOT_BOMB;
        case 0x014B: return AP_LOCATION_CORNERIA_BEHIND_DOORS_NEAR_CHECKPOINT_GOLD_RING;
        case 0x0171: return AP_LOCATION_CORNERIA_CHECKPOINT;
        case 0x020A: return AP_LOCATION_CORNERIA_AFTER_FALCOS_G_DIFFUSER_ISSUE_LASER_UPGRADE;
        case 0x020C: return AP_LOCATION_CORNERIA_AFTER_FALCOS_G_DIFFUSER_ISSUE_BOMB;
        case 0x025D: return AP_LOCATION_CORNERIA_WATER_SECTION_LAST_ARCH_GOLD_RING;
        case 0x0290: return AP_LOCATION_CORNERIA_LEFT_OF_WATERFALL_LASER_UPGRADE;
        case 0x02A4: return AP_LOCATION_CORNERIA_BEFORE_MISSION_COMPLETE_BOSS_LOWER_GOLD_RING;
        case 0x02A5: return AP_LOCATION_CORNERIA_BEFORE_MISSION_COMPLETE_BOSS_UPPER_GOLD_RING;
      }
      break;
    case LEVEL_METEO:
      switch (index) {
        case 0x0072: return AP_LOCATION_METEO_AFTER_STARTING_ASTEROIDS_GOLD_RING;
        case 0x00BB: return AP_LOCATION_METEO_END_OF_FIRST_TUNNEL_BOTTOM_BOMB;
        case 0x00BD: return AP_LOCATION_METEO_END_OF_FIRST_TUNNEL_MIDDLE_SILVER_RING;
        case 0x00BE: return AP_LOCATION_METEO_END_OF_FIRST_TUNNEL_TOP_GOLD_RING;
        case 0x00F2: return AP_LOCATION_METEO_BETWEEN_TWO_BIG_ASTEROIDS_BOMB;
        case 0x01DF: return AP_LOCATION_METEO_CHECKPOINT;
        case 0x028E: return AP_LOCATION_METEO_NEAR_WARP_RINGS_GOLD_RING;
        case 0x033E: return AP_LOCATION_METEO_JUST_BEFORE_BOSS_GOLD_RING;
      }
      break;
    // case LEVEL_FORTUNA:
    //   switch (index) {
    //   }
    //   break;
    case LEVEL_SECTOR_X:
      switch (index) {
        case 0x00E9: return AP_LOCATION_SECTOR_X_IN_DEBRIS_FIELD_LEFT_GOLD_RING;
        case 0x0113: return AP_LOCATION_SECTOR_X_CHECKPOINT;
        case 0x0146: return AP_LOCATION_SECTOR_X_BEHIND_ENEMY_AFTER_PEPPY_GETS_CHASED_RIGHT_GOLD_RING;
        case 0x0196: return AP_LOCATION_SECTOR_X_LEFT_PATH_JUST_AFTER_FORK_THROUGH_BOTTOM_SLOT_LASER_UPGRADE;
        case 0x01D2: return AP_LOCATION_SECTOR_X_LEFT_PATH_CLOSING_DOOR_SECTION_GOLD_RING;
        case 0x0254: return AP_LOCATION_SECTOR_X_LEFT_PATH_AFTER_CLOSING_DOOR_SECTION_BOMB;
        case 0x02B7: return AP_LOCATION_SECTOR_X_LEFT_PATH_BEHIND_FIRST_WARP_GATE_GOLD_RING;
        case 0x02C4: return AP_LOCATION_SECTOR_X_LEFT_PATH_AFTER_FIRST_WARP_GATE_UP_HIGH_BOMB;
        case 0x0392: return AP_LOCATION_SECTOR_X_LEFT_PATH_BEFORE_FINAL_WARP_GATE_GOLD_RING;
      }
      break;
    case LEVEL_TITANIA:
      switch (index) {
        case 0x0018: return AP_LOCATION_TITANIA_SECOND_FALLING_TOWER_FROM_START_BOMB;
        case 0x0028: return AP_LOCATION_TITANIA_THROUGH_TWO_LEANING_TOWERS_GOLD_RING;
        case 0x004F: return AP_LOCATION_TITANIA_AFTER_THREE_BONE_STRUCTURES_BOMB;
        case 0x0093: return AP_LOCATION_TITANIA_ABOVE_SKULL_SILVER_RING;
        case 0x00C5: return AP_LOCATION_TITANIA_ON_BRIDGE_GOLD_RING;
        case 0x00C6: return AP_LOCATION_TITANIA_RIGHT_OF_BRIDGE_GOLD_RING;
        case 0x010A: return AP_LOCATION_TITANIA_UPPER_LEFT_PATH_BOMB;
        case 0x011E: return AP_LOCATION_TITANIA_SUSPENDED_ABOVE_TWO_BRIDGES_SILVER_RING;
        case 0x015E: return AP_LOCATION_TITANIA_CHECKPOINT;
        case 0x0190: return AP_LOCATION_TITANIA_FALLING_TOWERS_SECTION_FIRST_BOMB;
        case 0x019C: return AP_LOCATION_TITANIA_FALLING_TOWERS_SECTION_GOLD_RING;
        case 0x01A5: return AP_LOCATION_TITANIA_FALLING_TOWERS_SECTION_SECOND_BOMB;
        case 0x01BE: return AP_LOCATION_TITANIA_FALLING_TOWERS_SECTION_THIRD_BOMB;
        case 0x020C: return AP_LOCATION_TITANIA_BEHIND_ARCHES_ON_THE_RIGHT_GOLD_RING;
        case 0x0221: return AP_LOCATION_TITANIA_UPPER_RIGHT_HILL_GOLD_RING;
        case 0x0231: return AP_LOCATION_TITANIA_FIRST_FALLING_TOWER_BEFORE_BOSS_SILVER_RING;
        case 0x0236: return AP_LOCATION_TITANIA_FIRST_FALLING_TOWER_BEFORE_BOSS_GOLD_RING;
        case 0x023A: return AP_LOCATION_TITANIA_SECOND_FALLING_TOWER_BEFORE_BOSS_SILVER_RING;
        case 0x023F: return AP_LOCATION_TITANIA_SECOND_FALLING_TOWER_BEFORE_BOSS_GOLD_RING;
      }
      break;
    // case LEVEL_BOLSE:
    //   switch (index) {
    //   }
    //   break;
    case LEVEL_SECTOR_Y:
      switch (index) {
        case 0x0021: return AP_LOCATION_SECTOR_Y_ABOVE_FRIENDLY_SHIP_NEAR_START_GOLD_RING;
        case 0x00DB: return AP_LOCATION_SECTOR_Y_BEFORE_CHECKPOINT_GOLD_RING;
        case 0x00D7: return AP_LOCATION_SECTOR_Y_CHECKPOINT;
        case 0x01B0: return AP_LOCATION_SECTOR_Y_BREAKING_THROUGH_THE_ENEMY_FLEET_BEGINNING_GOLD_RING;
        case 0x01CC: return AP_LOCATION_SECTOR_Y_BREAKING_THROUGH_THE_ENEMY_FLEET_MIDDLE_GOLD_RING;
        case 0x01E3: return AP_LOCATION_SECTOR_Y_BREAKING_THROUGH_THE_ENEMY_FLEET_END_GOLD_RING;
      }
      break;
    case LEVEL_AQUAS:
      switch (index) {
        case 0x00BD: return AP_LOCATION_AQUAS_CHECKPOINT;
      }
      break;
    case LEVEL_ZONESS:
      switch (index) {
        case 0x0073: return AP_LOCATION_ZONESS_BEFORE_KATT_APPEARS_BOTTOM_BOMB;
        case 0x0076: return AP_LOCATION_ZONESS_BEFORE_KATT_APPEARS_TOP_GOLD_RING;
        case 0x0077: return AP_LOCATION_ZONESS_BEFORE_KATT_APPEARS_MIDDLE_SILVER_RING;
        case 0x010F: return AP_LOCATION_ZONESS_CHECKPOINT;
        case 0x0121: return AP_LOCATION_ZONESS_AIM_FOR_THE_RUDDER_FIRST_GATE_LASER_UPGRADE;
        case 0x012D: return AP_LOCATION_ZONESS_AIM_FOR_THE_RUDDER_SECOND_GATE_LEFT_BOMB;
        case 0x0133: return AP_LOCATION_ZONESS_AIM_FOR_THE_RUDDER_THIRD_GATE_SILVER_RING;
      }
      break;
    // case LEVEL_SECTOR_Z:
    //   switch (index) {
    //   }
    //   break;
    case LEVEL_AREA_6:
      switch (index) {
        case 0x00A3: return AP_LOCATION_AREA_6_BELOW_EARLY_DEFENSE_STATION_GOLD_RING;
        case 0x00A4: return AP_LOCATION_AREA_6_ABOVE_EARLY_DEFENSE_STATION_LASER_UPGRADE;
        case 0x00E3: return AP_LOCATION_AREA_6_ANDROSS_TAUNT_GOLD_RING;
        case 0x00FA: return AP_LOCATION_AREA_6_CHECKPOINT;
        case 0x0115: return AP_LOCATION_AREA_6_NEAR_DEFENSE_STATION_AFTER_CHECKPOINT_GOLD_RING;
      }
      break;
    // case LEVEL_KATINA:
    //   switch (index) {
    //   }
    //   break;
    case LEVEL_SOLAR:
      switch (index) {
        case 0x005C: return AP_LOCATION_SOLAR_CHECKPOINT;
      }
      break;
    case LEVEL_MACBETH:
      switch (index) {
        case 0x0097: return AP_LOCATION_MACBETH_BEFORE_HILL_WITH_ROLLING_ROCKS_BOMB;
        case 0x00C6: return AP_LOCATION_MACBETH_ABOVE_ROLLING_ROCKS_GOLD_RING;
        case 0x00F9: return AP_LOCATION_MACBETH_ON_TRACKS_BEFORE_BRIDGE_GOLD_RING;
        case 0x0116: return AP_LOCATION_MACBETH_ON_TRACKS_AFTER_BRIDGE_GOLD_RING;
        case 0x0139: return AP_LOCATION_MACBETH_CHECKPOINT;
        case 0x0152: return AP_LOCATION_MACBETH_AFTER_FIRST_BUILDING_SILVER_RING;
        case 0x015C: return AP_LOCATION_MACBETH_BEFORE_BUILDINGS_THREE_AND_FOUR_SILVER_RING;
        case 0x0166: return AP_LOCATION_MACBETH_AFTER_BUILDINGS_THREE_AND_FOUR_RIGHT_SILVER_RING;
        case 0x016B: return AP_LOCATION_MACBETH_BEFORE_BUILDING_FIVE_SILVER_RING;
        case 0x016D: return AP_LOCATION_MACBETH_AFTER_BUILDING_FIVE_GOLD_RING;
        case 0x018A: return AP_LOCATION_MACBETH_UNDER_BRIDGE_AFTER_CHECKPOINT_BOMB;
        case 0x01D3: return AP_LOCATION_MACBETH_FIRST_BUILDING_AFTER_SWITCHER_GOLD_RING;
        case 0x01DA: return AP_LOCATION_MACBETH_SECOND_BUILDING_AFTER_SWITCHER_SILVER_RING;
        case 0x01EA: return AP_LOCATION_MACBETH_AFTER_MARKER_100_SILVER_RING;
        case 0x0280: return AP_LOCATION_MACBETH_BEFORE_MARKER_300_SILVER_RING;
      }
      break;
    case LEVEL_VENOM_1:
      switch (index) {
        case 0x0087: return AP_LOCATION_VENOM_1_NEAR_START_BOTTOM_GOLD_RING;
        case 0x0088: return AP_LOCATION_VENOM_1_NEAR_START_TOP_LASER_UPGRADE;
        case 0x02A8: return AP_LOCATION_VENOM_1_MAZE_R_R_R_GOLD_RING;
        case 0x02C1: return AP_LOCATION_VENOM_1_MAZE_L_L_GOLD_RING;
        case 0x02DA: return AP_LOCATION_VENOM_1_MAZE_R_R_L_L_GOLD_RING;
        case 0x039F: return AP_LOCATION_VENOM_1_END_OF_MAZE_R_R_R_R_GOLD_RING;
        case 0x03B3: return AP_LOCATION_VENOM_1_END_OF_MAZE_L_L_L_GOLD_RING;
        case 0x0405: return AP_LOCATION_VENOM_1_END_OF_MAZE_R_R_L_L_GOLD_RING;
        case 0x048C: return AP_LOCATION_VENOM_1_CHECKPOINT;
      }
      break;
  }
  return AP_LOCATION_NONE;
}
