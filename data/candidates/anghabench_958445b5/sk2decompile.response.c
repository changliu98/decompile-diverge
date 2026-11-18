static unsigned int uniphier_gpio_bank_to_reg(unsigned int bank) {
  unsigned int reg;
  reg = (bank + 1) * 8;
  if (reg >= UNIPHIER_GPIO_REG_MAX) reg += 16;
  return reg;
}