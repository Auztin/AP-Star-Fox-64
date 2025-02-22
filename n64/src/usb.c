#include "usb.h"
#include "n64/ed64.h"
#include "ap/ap.h"
#include "ap/commands.h"

void usb_init() {
  ed64_init();
}

u8 usb_read() {
  if (ed64_read(&ap.input, 8)) return 1;
  int size = ap.input.size-6;
  if (size > 0) {
    size--;
    size = size-size%4+4;
    if (size > 504 || ed64_read(ap.input.data, size)) return 1;
  }
  return 0;
}

u8 usb_write() {
  int size = ap.output.size+2;
  if (size < 8) size = 8;
  else if (size) {
    size--;
    size = size-size%4+4;
  }
  return ed64_write(&ap.output, size);
}

void usb_check() {
  disable_interrupts();
  if (!dma_busy()) {
    if (ed64_can_read()) usb_read();
    ap_input();
    ap_output();
    if (ap.output.cmd != AP_CMD_NONE && ed64_can_write()) {
      usb_write();
      ap.output.cmd = AP_CMD_NONE;
    }
  }
  enable_interrupts();
}
