uint8_t __sw_hweight16(uint16_t w) {
  w = w - ((w >> 1) & 0x5555);
  w = (w & 0x3333) + ((w >> 2) & 0x3333);
  w = w + (w >> 4);
  w = w & 0x0F0F;
  w = w + (w >> 8);
  w = w & 0x00FF;
  return (uint8_t) w;
}