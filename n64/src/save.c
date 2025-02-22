#include <string.h>
#include "save.h"
#include "util.h"
#include "n64/dma.h"
#include "ap/version.h"
#include "sf/save.h"

save_t save = {0,};

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

void save_load_slot(char* seed) {
  int slot = -1;
  for (int i = 0; i < SAVE_SLOTS; i++) {
    if (!memcmp(save.data.custom[i].seed, seed, sizeof(save.data.custom[i].seed))) {
      slot = i;
      break;
    }
  }
  if (slot == -1) {
    slot = save.data.recents[SAVE_SLOTS-1];
    memset(&save.data.custom[slot], 0, sizeof(*save.data.custom));
    memcpy(save.data.custom[slot].seed, seed, sizeof(save.data.custom[slot].seed));
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
}
