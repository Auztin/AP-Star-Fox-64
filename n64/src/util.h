#pragma once

#include "n64/types.h"

enum UTIL_INJECT {
  UTIL_INJECT_RAW,
  UTIL_INJECT_JUMP,
  UTIL_INJECT_FUNCTION,
  UTIL_INJECT_BRANCH,
  UTIL_INJECT_RETVALUE,
  UTIL_INJECT_RETURN,
};

void util_inject(enum UTIL_INJECT type, u32 addr, u32 data, u8 addNOP);
bool get_bit(u8* data, u32 id);
bool change_bit(u8* data, u32 id, bool value);
bool set_bit(u8* data, u32 id);
bool unset_bit(u8* data, u32 id);
void csrand(u32 seed);
u32 crand();
