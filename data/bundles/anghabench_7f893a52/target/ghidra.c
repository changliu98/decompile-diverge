int uniphier_ld11_get_gpio_muxval(uint pin,uint gpio_offset)

{
  uint gpio_offset_local;
  uint pin_local;
  undefined4 local_c;
  
  if ((gpio_offset == 0x84) || (gpio_offset == 0x87)) {
    local_c = 0xd;
  }
  else if ((gpio_offset < 0x78) || (0x8f < gpio_offset)) {
    local_c = 0xf;
  }
  else {
    local_c = 0xe;
  }
  return local_c;
}