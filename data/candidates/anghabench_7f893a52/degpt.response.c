uint uniphier_ld11_get_gpio_muxval(uint gpio_pin, uint gpio_register_offset)
{
  // Check if the GPIO offset corresponds to specific special pins
  if ((gpio_register_offset == 0x84) || (gpio_register_offset == 0x87)) {
    // Return mux value 0xd for these specific offsets
    return 0xd;
  }
  // Check if the GPIO offset is outside the valid range [0x78, 0x8f]
  else if ((gpio_register_offset < 0x78) || (0x8f < gpio_register_offset)) {
    // Return default mux value 0xf for out-of-range offsets
    return 0xf;
  }
  else {
    // Return default mux value 0xe for valid offsets within the range
    return 0xe;
  }
}