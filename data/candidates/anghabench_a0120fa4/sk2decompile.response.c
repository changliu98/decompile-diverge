static inline unsigned REG_A5XX_VFD_FETCH_BASE_HI(unsigned vfd) {
  unsigned location;
  location = (0x0000E003 + (0x00000004 * vfd));
  return location;
}