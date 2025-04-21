#pragma once

// Automatically generated using enum_gen.py

typedef enum {
  AP_CMD_NONE = 0,
  AP_CMD_HANDSHAKE = 1,
  AP_CMD_PING = 2,
  AP_CMD_PONG = 3,
  AP_CMD_SEED = 4,
  AP_CMD_OPTIONS = 5,
  AP_CMD_READY = 6,
  AP_CMD_LOCATIONS = 7,
  AP_CMD_ITEMS = 8,
  AP_CMD_DEATHLINK = 9,
  AP_CMD_RINGLINK = 10,
  AP_CMD_MAX = 11,
} ap_cmd_t;
