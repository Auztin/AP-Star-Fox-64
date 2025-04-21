#pragma once

#include "n64/types.h"
#include "options.h"
#include "locations.h"
#include "items.h"

#define PACKET_SIZE (512-4)

typedef struct {
  u16 name;
  u16 value;
} ap_packet_option_t;

typedef struct __attribute__ ((aligned (16))) {
  u16 size;
  u16 cmd;
  union {
    struct {
      char header[4];
      char data[PACKET_SIZE-4];
    };
    struct {
      u32 version;
      char msg[4];
    } handshake;
    struct {
      u16 team;
      u16 slot;
      char data[20];
    } seed;
    s16 ringlink;
    ap_packet_option_t options[PACKET_SIZE/sizeof(ap_packet_option_t)];
    u32 locations[PACKET_SIZE/4];
    u32 items[PACKET_SIZE/4];
  };
} ap_packet_t;

typedef struct {
  ap_packet_t input;
  ap_packet_t output;
  s16 ping_timer;
  u8 state;
  bool ready;
  u8 sent_locations[AP_LOCATION_MAX_BYTES/8];
  u8 received_items[AP_ITEM_MAX];
  struct {
    u8 deathlink;
  } in;
  struct {
    u8 deathlink;
  } out;
} ap_t;
extern ap_t ap;


void ap_init();
void ap_input();
void ap_output();
