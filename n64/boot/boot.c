#include <stdint.h>

typedef struct PI_regs_s {
  uint32_t ram_address;
  uint32_t pi_address;
  uint32_t read_length;
  uint32_t write_length;
  uint32_t status;
} PI_regs_t;

#define PI_STATUS_DMA_BUSY ( 1 << 0 )
#define PI_STATUS_IO_BUSY  ( 1 << 1 )
static volatile struct PI_regs_s * const PI_regs = (struct PI_regs_s *)0xA4600000;

void boot(void) {
  // request to load our payload in expansion pak memory
  PI_regs->ram_address  = 0x00400000;
  PI_regs->pi_address   = 0x10C00000;
  PI_regs->write_length = 0x00100000;
  while (PI_regs->status & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY));
  // let the game finally init
  asm("J init_game");
}
