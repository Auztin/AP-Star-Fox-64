#include "n64/types.h"
#include "util.h"
#include "main.h"
#include "save.h"
#include "hud.h"
#include "radio.h"
#include "object.h"

u32 inject_hooks() {
  main_init();

  util_inject(UTIL_INJECT_FUNCTION, 0x8000435C, (u32)main_loop, 1);

  util_inject(UTIL_INJECT_FUNCTION, 0x800A1BD8, (u32)main_load_scene_data, 0);
  util_inject(UTIL_INJECT_JUMP    , 0x80088564, (u32)main_pre_venom, 1);
  util_inject(UTIL_INJECT_RAW     , 0x80088648, 0, 1);

  util_inject(UTIL_INJECT_RETURN  , 0x80023F50, 1, 1); // convince game eeprom exists
  util_inject(UTIL_INJECT_JUMP    , 0x800234B0, (u32)save_eeprom_read, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x800237B0, (u32)save_eeprom_write, 1);

  util_inject(UTIL_INJECT_FUNCTION, 0x80089304, (u32)hud_pause_draw_selections, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x8008930C, 0x800895E8, 1);
  util_inject(UTIL_INJECT_FUNCTION, 0x80088A54, (u32)hud_pause_check_input, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x80088A5C, 0x8008903C, 0);
  util_inject(UTIL_INJECT_RAW     , 0x80088A60, 0x3C088016, 0);

  util_inject(UTIL_INJECT_JUMP    , 0x800BA808, (u32)radio_play, 1);

  util_inject(UTIL_INJECT_JUMP    , 0x800A3F50, (u32)main_check_medal, 1);

  util_inject(UTIL_INJECT_JUMP    , 0x80061444, (u32)object_item_init, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x800612B8, (u32)object_info, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x80061864, (u32)object_item_load, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x800660F0, (u32)object_item_drop, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x8005C900, (u32)object_draw_silver_ring, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x800680B0, 0x800680F8, 1);
  util_inject(UTIL_INJECT_FUNCTION, 0x800680F8, (u32)object_collect_silver_ring, 0);
  util_inject(UTIL_INJECT_RAW     , 0x800680FC, 0x02002025, 0);
}
