#include "util.h"

void util_inject(enum UTIL_INJECT type, u32 addr, u32 data, u8 addNOP) {
  u32 op = 0;
  u32 extra = 0;
  switch (type) {
    case UTIL_INJECT_RAW:
      (*(vu32*)addr) = data;
      return;
    case UTIL_INJECT_JUMP:
      op = 0x08000000;
      extra = (data & 0x01FFFFFF)/4;
      break;
    case UTIL_INJECT_FUNCTION:
      op = 0x0C000000;
      extra = (data & 0x01FFFFFF)/4;
      break;
    case UTIL_INJECT_BRANCH:
      op = 0x10000000;
      extra = (u16)(data/4-1);
      break;
    case UTIL_INJECT_RETVALUE:
      op = 0x24020000;
      extra = data & 0xFFFF;
      break;
    case UTIL_INJECT_RETURN:
      op = 0x03E00008;
      extra = 0;
      if (addNOP) util_inject(UTIL_INJECT_RETVALUE, addr + 4, data, 0);
      addNOP = 0;
      break;
  }
  if (op) {
    (*(vu32*)addr) = op | extra;
    if (addNOP) (*(vu32*)(addr + 4)) = 0;
  }
}

bool get_bit(u8* data, u32 id) {
  u32 byte = id/8;
  u8 bit = 1 << (id % 8);
  return (data[byte] & bit) ? 1 : 0;
}

bool change_bit(u8* data, u32 id, bool value) {
  u32 byte = id/8;
  u8 bit = 1 << (id % 8);
  bool ret = data[byte] & bit;
  if (value) data[byte] |= bit;
  else data[byte] &= ~bit;
  return ret ? 1 : 0;
}

bool set_bit(u8* data, u32 id) {
  return change_bit(data, id, 1);
}

bool unset_bit(u8* data, u32 id) {
  return change_bit(data, id, 0);
}
