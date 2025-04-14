#include <string.h>
#include "save.h"
#include "util.h"
#include "radio.h"
#include "n64/dma.h"
#include "ap/version.h"
#include "sf/save.h"

save_t save = {0,};

void save_init_random() {
  u32 ap_seed[5];
  memcpy(ap_seed, ap_save.seed, 20);
  typedef union {
    u8 bytes[4];
    u32 i;
  } seed_t;
  seed_t seed;
  for (int i = 0; i < 4; i++) {
    csrand(ap_seed[i]);
    seed.bytes[i] = crand()%256;
  }
  csrand(ap_seed[4]);
  for (int i = 0; i < ap_save.team; i++) crand();
  int iters = crand()%129;
  for (int i = 0; i < ap_save.slot; i++) crand();
  iters += crand()%128;
  csrand(seed.i);
  for (; iters; iters--) crand();
  radio_randomize();
}

void save_init() {
  const u32 size = sizeof(save.data);
  dma_read_raw_async(&save.data, 0x08000000, size);
  if (save.data.magic_start != SAVE_MAGIC || save.data.magic_end != SAVE_MAGIC || save.data.version != AP_VERSION.as_int) {
    memset(&save.data, 0, size);
    save.data.magic_start = SAVE_MAGIC;
    save.data.magic_end = SAVE_MAGIC;
    save.data.version = AP_VERSION.as_int;
    for (int i = 0; i < SAVE_SLOTS; i++) save.data.recents[i] = i;
    save_sram_write();
  }
  save.slot = save.data.recents[0];
  save_init_random();
}

void save_sram_write() {
  if (!save.dirty) return;
  const u32 size = sizeof(save.data);
  dma_write_raw_async(&save.data, 0x08000000, size);
  save.dirty = false;
}

u32 save_eeprom_read(u32 _unused, u32 offset, u32 *ramAddr) {
  offset *= 2;
  ramAddr[0] = save.data.eeprom[offset];
  ramAddr[1] = save.data.eeprom[offset+1];
  return 0;
}

u32 save_eeprom_write(u32 _unused, u32 offset, u32 *ramAddr) {
  offset *= 2;
  save.data.eeprom[offset] = ramAddr[0];
  save.data.eeprom[offset+1] = ramAddr[1];
  save.dirty = true;
  return 0;
}

void save_sync_medals() {
  const ap_location_t locations[] = {
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
    AP_LOCATION_SOLAR_MEDAL,
    AP_LOCATION_VENOM_MEDAL,
    AP_LOCATION_VENOM_MEDAL,
  };
  for (int i = 0; i < SAVE_LEVELS_MAX; i++) {
    sf_save_level_t* level = &sf_save.levels[i];
    level->played = true;
    level->clear = true;
    level->medal = get_bit(ap_save.locations, locations[i]);
  }
}

void save_load_slot(u16 ap_team, u16 ap_slot, char* ap_seed) {
  int slot = -1;
  save_custom_data_t* data;
  for (int i = 0; i < SAVE_SLOTS; i++) {
    data = &save.data.custom[i];
    if (!memcmp(data->seed, ap_seed, sizeof(data->seed)) && data->team == ap_team && data->slot == ap_slot) {
      slot = i;
      break;
    }
  }
  if (slot == -1) {
    slot = save.data.recents[SAVE_SLOTS-1];
    memset(data, 0, sizeof(save_custom_data_t));
    memcpy(data->seed, ap_seed, sizeof(data->seed));
    data->team = ap_team;
    data->slot = ap_slot;
    save.dirty = true;
  }
  save.slot = slot;
  u8* recents = save.data.recents;
  for (int i = 0; i < SAVE_SLOTS; i++) {
    int tmp = recents[i];
    recents[i] = slot;
    slot = tmp;
    if (save.slot == slot) break;
  }
  save_sync_medals();
  save_init_random();
}
