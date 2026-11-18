static inline unsigned REG_A5XX_RB_MRT_FLAG_BUFFER_ARRAY_PITCH(
    unsigned index) {
  unsigned location;
  location = (0x0000E000UL) + (0x00001000UL * index) + 0x00000000UL;
  return location;
}