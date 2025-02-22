#include "n64/types.h"
#include "util.h"
#include "main.h"
#include "save.h"

u32 inject_hooks() {
  main_init();

  util_inject(UTIL_INJECT_FUNCTION, 0x8000435C, (u32)main_loop, 1);

  util_inject(UTIL_INJECT_FUNCTION, 0x800A1BD8, (u32)main_load_scene_data, 0);
  util_inject(UTIL_INJECT_JUMP    , 0x80088564, (u32)main_pre_venom, 1);

  util_inject(UTIL_INJECT_RETURN  , 0x80023F50, 1, 1); // convince game eeprom exists
  util_inject(UTIL_INJECT_JUMP    , 0x800234B0, (u32)save_eeprom_read, 1);
  util_inject(UTIL_INJECT_JUMP    , 0x800237B0, (u32)save_eeprom_write, 1);
}
