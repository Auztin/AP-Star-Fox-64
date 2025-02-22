#pragma once

#include "dma.h"
#include "types.h"

#define ED64_REG_BASE         0x1F800000
#define ED64_REG_KEY          0x8004
#define ED64_REG_SYS_CFG      0x8000
#define ED64_REG_USB_CFG      0x0004
#define ED64_REG_USB_DAT      0x0400

#define ED64_USB_STA_ACT      0x0200
#define ED64_USB_STA_RXF      0x0400
#define ED64_USB_STA_TXE      0x0800
#define ED64_USB_STA_PWR      0x1000
// #define ED64_USB_STA_BSY      0x2000

#define ED64_USB_LE_CFG       0x8000
#define ED64_USB_LE_CTR       0x4000

#define ED64_USB_CFG_ACT      0x0200
#define ED64_USB_CFG_RD       0x0400
#define ED64_USB_CFG_WR       0x0000

#define ED64_USB_CMD_RD_NOP   (ED64_USB_LE_CFG | ED64_USB_LE_CTR | ED64_USB_CFG_RD)
#define ED64_USB_CMD_RD       (ED64_USB_LE_CFG | ED64_USB_LE_CTR | ED64_USB_CFG_RD | ED64_USB_CFG_ACT)
#define ED64_USB_CMD_WR_NOP   (ED64_USB_LE_CFG | ED64_USB_LE_CTR | ED64_USB_CFG_WR)
#define ED64_USB_CMD_WR       (ED64_USB_LE_CFG | ED64_USB_LE_CTR | ED64_USB_CFG_WR | ED64_USB_CFG_ACT)

#define ED64_REG_ADDR(reg)    (0xA0000000 | ED64_REG_BASE | (reg))

u8 ed64_can_read();
u8 ed64_can_write();
u8 ed64_read(void *ram_address, u32 len);
u8 ed64_write(void *ram_address, u32 len);
void ed64_init();
