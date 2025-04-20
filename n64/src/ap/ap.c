#include <string.h>
#include "ap.h"
#include "commands.h"
#include "states.h"
#include "main.h"
#include "map.h"
#include "version.h"
#include "util.h"
#include "save.h"
#include "hit_count.h"

ap_t ap = {0, };
extern ap_packet_t* AP_INPUT_PTR;
extern ap_packet_t* AP_OUTPUT_PTR;

void ap_init() {
  AP_INPUT_PTR = &ap.input;
  AP_OUTPUT_PTR = &ap.output;
}

void ap_input() {
  ap.ping_timer += main.delta;
  if (ap.ping_timer >= 1000) ap.ping_timer = 0;
  int state = ap.state & ~AP_STATE_PINGED;
  if (state != AP_STATE_CONNECTED) ap.ready = false;
  switch (state) {
    case AP_STATE_DISCONNECTED:
      switch (ap.input.cmd) {
        case AP_CMD_NONE:
          if (!ap.ping_timer) {
            ap.output.cmd = AP_CMD_HANDSHAKE;
            ap.output.handshake.version = AP_VERSION.as_int;
            memcpy(ap.output.handshake.msg, "HELO", 4);
            ap.output.size = 10;
          }
          break;
        case AP_CMD_HANDSHAKE:
          if (!memcmp(ap.input.handshake.msg, "'LO!", 4) && ap.input.handshake.version == AP_VERSION.as_int) {
            ap.state = AP_STATE_CONNECTING;
            ap.output.cmd = AP_CMD_PING;
            ap.output.size = 2;
          }
          break;
      }
      break;
    case AP_STATE_CONNECTING:
      if (!ap.ping_timer) ap.state = AP_STATE_DISCONNECTED;
      switch (ap.input.cmd) {
        case AP_CMD_NONE:
          break;
        case AP_CMD_PONG:
          ap.state = AP_STATE_CONNECTED;
          break;
        default:
          ap.state = AP_STATE_DISCONNECTED;
      }
      break;
    case AP_STATE_CONNECTED:
      if (!ap.ping_timer) {
        if (ap.state & AP_STATE_PINGED) {
          ap.state = AP_STATE_DISCONNECTED;
          break;
        }
        ap.output.data[0] = 0;
        ap.output.cmd = AP_CMD_PING;
        ap.output.size = 2;
        ap.state |= AP_STATE_PINGED;
        break;
      }
      switch (ap.input.cmd) {
        case AP_CMD_NONE:
          break;
        case AP_CMD_PING:
          ap.output.data[0] = 0;
          ap.output.cmd = AP_CMD_PONG;
          ap.output.size = 2;
          break;
        case AP_CMD_PONG:
          ap.state &= ~AP_STATE_PINGED;
          ap.ping_timer = 0;
          break;
        case AP_CMD_SEED:
          save_load_slot(ap.input.seed.team, ap.input.seed.slot, ap.input.seed.data);
          memset(&ap.sent_locations, 0, sizeof(ap.sent_locations));
          memset(&ap.received_items, 0, sizeof(ap.received_items));
          break;
        case AP_CMD_OPTIONS:
          for (int i = 0; i < (ap.input.size-2)/sizeof(*ap.input.options); i++) {
            ap_packet_option_t* option = &ap.input.options[i];
            if (option->name >= AP_OPTION_MAX) break;
            ap_save.options[option->name] = option->value;
          }
          break;
        case AP_CMD_READY:
          ap.ready = true;
          break;
        case AP_CMD_LOCATIONS:
          for (int i = 0; i < (ap.input.size-2)/sizeof(*ap.input.locations); i++) {
            u32 location = ap.input.locations[i];
            if (location >= AP_LOCATION_MAX) break;
            set_bit(ap_save.locations, location);
          }
          map.check = true;
          save.dirty = true;
          break;
        case AP_CMD_ITEMS:
          for (int i = 0; i < (ap.input.size-2)/sizeof(*ap.input.items); i++) {
            u32 item = ap.input.items[i];
            if (item >= AP_ITEM_MAX) break;
            ap.received_items[item]++;
            ap_save.items[item] = ap.received_items[item];
          }
          map.check = true;
          save.dirty = true;
          break;
        case AP_CMD_BOUNCE:
          if (ap.input.bounce_packet.header == AP_ITEM_RING_LINK){
            s16 received_rings = (s16)ap.input.bounce_packet.data;

            // Reducing hit counter requires setting both current and target hits
            // at the same time, or the UI spinner will flip out
            if (received_rings < 0){
              if (sf_target_hits + received_rings <= 0) sf_current_hits = sf_target_hits = 0;
              else {
                sf_current_hits += received_rings;
                sf_target_hits += received_rings;
              }
            }
            else{
              // Just set target hits. Looks nicer with the UI animation.
              if (sf_target_hits + received_rings >= 511) sf_target_hits = 511;
              else sf_target_hits += received_rings;
            }

            main.last_player_hits = sf_target_hits; // Prevent a ringlink reflection

          }
        case AP_CMD_DEATHLINK:
          ap.in.deathlink++;
          break;
        default:
          ap.state = AP_STATE_DISCONNECTED;
      }
      break;
  }
  ap.input.cmd = AP_CMD_NONE;
}

void ap_output() {
  if (ap.output.cmd != AP_CMD_NONE) return;
  int offset = 0;
  for (int i = 0; i < AP_LOCATION_MAX_BYTES/8; i++) {
    u8 location = ap_save.locations[i];
    u8 sent_location = ap.sent_locations[i];
    if (location == sent_location) continue;
    u32 base = i*8;
    for (int b = 0; b < 8; b++) {
      u32 id = base+b;
      if (!get_bit(ap_save.locations, id) || set_bit(ap.sent_locations, id)) continue;
      ap.output.locations[offset++] = id;
      if (offset >= countof(ap.output.locations)) goto locations;
    }
  }
  locations:
  if (offset) {
    ap.output.cmd = AP_CMD_LOCATIONS;
    ap.output.size = 2+offset*sizeof(*ap.output.locations);
    ap.ping_timer = 0;
    return;
  }
  if (ap.out.deathlink) {
    ap.out.deathlink--;
    ap.output.cmd = AP_CMD_DEATHLINK;
    ap.output.size = 2;
    ap.ping_timer = 0;
    return;
  }
  transmit_ring_message();
}
