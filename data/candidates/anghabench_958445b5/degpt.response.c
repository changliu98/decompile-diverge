uint gpio_bank_to_register(uint gpio_bank_index)
{
  uint register_offset = (gpio_bank_index + 1) * 8;
  if (UNIPHIER_GPIO_IRQ_EN <= register_offset) {
    register_offset += 0x10;
  }
  return register_offset;
}