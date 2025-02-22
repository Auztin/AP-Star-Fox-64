// modified from libdragon: https://github.com/DragonMinded/libdragon/

#pragma once

#include <stdint.h>

int dma_busy();
void dma_wait();
void data_cache_hit_writeback_invalidate(volatile void * addr, unsigned long length);
void data_cache_hit_writeback(volatile void * addr, unsigned long length);
void disable_interrupts();
void enable_interrupts();
void dma_read_raw_async(void * ram_address, unsigned long pi_address, unsigned long len);
void dma_write_raw_async(void * ram_address, unsigned long pi_address, unsigned long len);
uint32_t io_read(uint32_t pi_address);
void io_write(uint32_t pi_address, uint32_t data);
