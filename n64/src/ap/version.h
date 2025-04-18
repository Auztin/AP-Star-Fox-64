#pragma once

// Automatically generated using enum_gen.py

#include "n64/types.h"

typedef union {
  struct {
    u16 major;
    u8  minor;
    u8  build;
  };
  u32 as_int;
} ap_version_t;
static const ap_version_t AP_VERSION = {.major=0, .minor=3, .build=0};
