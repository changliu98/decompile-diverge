uint uniphier_gpio_bank_to_reg(uint bank)

{
  uint reg;
  uint bank_local;
  
  reg = (bank + 1) * 8;
  if (UNIPHIER_GPIO_IRQ_EN <= reg) {
    reg = reg + 0x10;
  }
  return reg;
}