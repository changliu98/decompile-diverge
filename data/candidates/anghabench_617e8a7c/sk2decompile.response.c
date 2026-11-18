static inline unsigned REG_A3XX_VFD_FETCH(unsigned i) {
  unsigned location;
  location = (0x00001306 + (i << 1));
  return location;
}