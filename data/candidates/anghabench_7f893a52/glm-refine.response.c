int __cdecl uniphier_ld11_get_gpio_muxval(unsigned int pin, unsigned int gpio_offset)
{
  // Specific pins have a special multiplexer value
  if (gpio_offset == 0x84 || gpio_offset == 0x87) // 132 and 135 in decimal
    return 13;

  // Check if the offset is outside the 0x78 - 0x8F range
  if (gpio_offset < 0x78 || gpio_offset > 0x8F)
    return 15;

  // Default value for offsets within the 0x78 - 0x8F range
  return 14;
}