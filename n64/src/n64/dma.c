// modified from libdragon: https://github.com/DragonMinded/libdragon/

#include "dma.h"

#define PI_STATUS_DMA_BUSY ( 1 << 0 )
#define PI_STATUS_IO_BUSY  ( 1 << 1 )
#define PI_STATUS_ERROR    ( 1 << 2 )
#define PI_STATUS_RESET    ( 1 << 0 )
#define PI_STATUS_CLR_INTR ( 1 << 1 )

typedef struct PI_regs_s {
    volatile void * ram_address;
    uint32_t pi_address;
    uint32_t read_length;
    uint32_t write_length;
    uint32_t status;
} PI_regs_t;
static volatile struct PI_regs_s * const PI_regs = (struct PI_regs_s *)0xA4600000;

#define cache_op(op, linesize) ({ \
  if (length) { \
    void *cur = (void*)((unsigned long)addr & ~(linesize-1)); \
    int count = (int)length + (addr-cur); \
    for (int i = 0; i < count; i += linesize) \
      asm ("\tcache %0,(%1)\n"::"i" (op), "r" (cur+i)); \
  } \
})

#define C0_STATUS() ({ \
    uint32_t x; \
    asm volatile("mfc0 %0,$12":"=r"(x)); \
    x; \
})
#define C0_WRITE_STATUS(x) ({ \
    asm volatile("mtc0 %0,$12"::"r"(x)); \
})
#define C0_STATUS_IE 0x00000001

uint32_t interrupt_sr = 0;
uint32_t interrupt_depth = 0;

void data_cache_hit_writeback_invalidate(volatile void * addr, unsigned long length) {
  cache_op(0x15, 16);
}

void data_cache_hit_writeback(volatile void * addr, unsigned long length) {
  cache_op(0x19, 16);
}

int dma_busy() {
  return PI_regs->status & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY);
}

void dma_wait() {
  while (dma_busy());
}

void disable_interrupts() {
  if (!interrupt_depth) {
    interrupt_sr = C0_STATUS();
    C0_WRITE_STATUS(interrupt_sr & ~C0_STATUS_IE);
  }
  interrupt_depth++;
}

void enable_interrupts() {
  if (interrupt_depth == 0) return;
  interrupt_depth--;
  if (!interrupt_depth) {
    C0_WRITE_STATUS(interrupt_sr);
  }
}

void dma_read_raw_async(void * ram_address, unsigned long pi_address, unsigned long len) {
  data_cache_hit_writeback_invalidate(ram_address, len);
  ram_address = (void*)((uint32_t)ram_address & 0x1FFFFFFF);
  disable_interrupts();
  dma_wait();
  PI_regs->ram_address = (void*)ram_address;
  PI_regs->pi_address = pi_address;
  PI_regs->write_length = len-1;
  dma_wait();
  PI_regs->status = PI_STATUS_CLR_INTR;
  enable_interrupts();
}

void dma_write_raw_async(void * ram_address, unsigned long pi_address, unsigned long len) {
  data_cache_hit_writeback(ram_address, len);
  ram_address = (void*)((uint32_t)ram_address & 0x1FFFFFFF);
  disable_interrupts();
  dma_wait();
  PI_regs->ram_address = (void*)ram_address;
  PI_regs->pi_address = pi_address;
  PI_regs->read_length = len-1;
  dma_wait();
  PI_regs->status = PI_STATUS_CLR_INTR;
  enable_interrupts();
}

uint32_t io_read(uint32_t pi_address) {
  uint32_t retval;
  disable_interrupts();
  dma_wait();
  retval = *(volatile uint32_t*)((void*)(pi_address | 0xA0000000));
  enable_interrupts();
  return retval;
}

void io_write(uint32_t pi_address, uint32_t data) {
  volatile uint32_t *uncached_address = (uint32_t*)(pi_address | 0xA0000000);
  disable_interrupts();
  dma_wait();
  *uncached_address = data;
  enable_interrupts();
}
