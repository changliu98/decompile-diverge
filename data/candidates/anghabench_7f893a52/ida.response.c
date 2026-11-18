int __cdecl uniphier_ld11_get_gpio_muxval(unsigned int pin, unsigned int gpio_offset)
{
  if ( gpio_offset == 132 || gpio_offset == 135 )
    return 13;
  if ( gpio_offset < 0x78 || gpio_offset > 0x8F )
    return 15;
  return 14;
}