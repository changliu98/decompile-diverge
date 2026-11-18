static inline unsigned REG_A3XX_GRAS_CL_USER_PLANE_X(unsigned index) {
  unsigned location;
  location = (0x0C00 + (index << 2));
  return location;
}