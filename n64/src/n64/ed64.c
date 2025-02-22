#include "ed64.h"
#include "dma.h"

u32 ed64_reg_read(u32 reg) {
  return io_read(ED64_REG_ADDR(reg));
}

void ed64_reg_write(u32 reg, u32 val) {
  io_write(ED64_REG_ADDR(reg), val);
}

u8 ed64_busy() {
  u32 timeout = 0;
  while ((ed64_reg_read(ED64_REG_USB_CFG) & ED64_USB_STA_ACT) != 0) {
    if (timeout++ != 8192) continue;
    ed64_reg_write(ED64_REG_USB_CFG, ED64_USB_CMD_RD_NOP);
    return 1;
  }
  return 0;
}

u8 ed64_can_read() {
  if ((ed64_reg_read(ED64_REG_USB_CFG) & (ED64_USB_STA_PWR | ED64_USB_STA_RXF)) == ED64_USB_STA_PWR) return 1;
  return 0;
}

u8 ed64_can_write() {
  if ((ed64_reg_read(ED64_REG_USB_CFG) & (ED64_USB_STA_PWR | ED64_USB_STA_TXE)) == ED64_USB_STA_PWR) return 1;
  return 0;
}

u8 ed64_read(void *ram_address, u32 len) {
  u16 blen, baddr;
  ed64_reg_write(ED64_REG_USB_CFG, ED64_USB_CMD_RD_NOP);
  while (len) {
    blen = 512;
    if (blen > len) blen = len;
    baddr = 512 - blen;
    ed64_reg_write(ED64_REG_USB_CFG, ED64_USB_CMD_RD | baddr);
    if (ed64_busy()) return 1;
    dma_read_raw_async(ram_address, ED64_REG_ADDR(ED64_REG_USB_DAT + baddr), blen);
    ram_address += blen;
    len -= blen;
  }
  return 0;
}

u8 ed64_write(void *ram_address, u32 len) {
  u16 blen, baddr;
  ed64_reg_write(ED64_REG_USB_CFG, ED64_USB_CMD_WR_NOP);
  while (len) {
    blen = 512;
    if (blen > len) blen = len;
    baddr = 512 - blen;
    dma_write_raw_async(ram_address, ED64_REG_ADDR(ED64_REG_USB_DAT + baddr), blen);
    ed64_reg_write(ED64_REG_USB_CFG, ED64_USB_CMD_WR | baddr);
    if (ed64_busy()) return 1;
    ram_address += 512;
    len -= blen;
  }
  return 0;
}

void ed64_init() {
  ed64_reg_write(ED64_REG_KEY, 0xAA55);
  ed64_reg_write(ED64_REG_SYS_CFG, 0);

  ed64_reg_write(ED64_REG_USB_CFG, ED64_USB_CMD_RD_NOP);
  while (ed64_can_read()) {
    ed64_reg_write(ED64_REG_USB_CFG, ED64_USB_CMD_RD);
    if (ed64_busy()) break;
  }
}
