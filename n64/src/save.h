#pragma once

#include "n64/types.h"
#include "ap/options.h"
#include "ap/locations.h"
#include "ap/items.h"
#include "sf/map.h"

#define SAVE_MAGIC 0x005F6400
#define SAVE_SLOTS 3

typedef struct {
  u8 peppy : 1;
  u8 slippy : 1;
  u8 falco : 1;
  u16 score;
} save_custom_data_planet_t;

typedef struct {
  u16 team;
  u16 slot;
  char seed[20];
  u8 options[AP_OPTION_MAX];
  u8 locations[AP_LOCATION_MAX_BYTES/8];
  u8 items[AP_ITEM_MAX];
  save_custom_data_planet_t planets[PLANET_MAX];
  union {
    struct {
      u16 falco;
      u16 slippy;
      u16 peppy;
    };
    s16 team[3];
  } shields;
  struct {
    u8 wolf : 1;
    u8 leon : 1;
    u8 pigma : 1;
    u8 andrew : 1;
  } star_wolf_alive;
  u8 bombs : 4;
  u8 lasers : 2;
  u8 gold_rings : 2;
  u8 great_fox_intact : 1;
  s8 lives;
} save_custom_data_t;

typedef struct {
  u32 magic_start;
  u32 version;
  u32 eeprom[128];
  u8 recents[SAVE_SLOTS];
  save_custom_data_t custom[SAVE_SLOTS];
  u32 magic_end;
} save_data_t;

typedef struct {
  u8 slot;
  bool dirty;
  save_data_t data;
} save_t;
extern save_t save;
#define ap_save (save.data.custom[save.slot])

void save_init();
void save_sram_write();
u32 save_eeprom_read(u32 _unused, u32 offset, u32 *ramAddr);
u32 save_eeprom_write(u32 _unused, u32 offset, u32 *ramAddr);
void save_load_slot(u16 ap_team, u16 ap_slot, char* ap_seed);
void save_sync_medals();
