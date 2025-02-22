#pragma once

#define TICKS_PER_MILLISECOND (93750000/2/1000)

#define C0_COUNT() ({ \
    uint32_t x; \
    asm volatile("mfc0 %0,$9":"=r"(x)); \
    x; \
})
