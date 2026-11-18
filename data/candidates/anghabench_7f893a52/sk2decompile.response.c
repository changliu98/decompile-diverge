static unsigned int uniphier_ld11_get_gpio_muxval(unsigned int bank,
                                                  unsigned int pin) {
  if (pin == 0x84 || pin == 0x87) return 13;
  if (pin >= 0x78 && pin <= 0x97) return 14;
  return 15;
}