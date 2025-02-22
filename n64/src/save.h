#pragma once

// #include "util.h"
#include "n64/types.h"
#include "ap/options.h"
#include "ap/locations.h"
#include "ap/items.h"

#define SAVE_MAGIC 0x005F6400
#define SAVE_SLOTS 3

typedef struct {
  u32 magic_start;
  u32 version;
  u32 eeprom[128];
  u8 recents[SAVE_SLOTS];
  struct {
    char seed[20];
    u8 options[AP_OPTION_MAX];
    u8 locations[AP_LOCATION_MAX_BYTES/8];
    u8 items[AP_ITEM_MAX];
  } custom[SAVE_SLOTS];
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
void save_load_slot(char* seed);
void save_sync_medals();
