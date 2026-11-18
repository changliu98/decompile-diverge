static int i2s_sf_sclkdiv(int div, unsigned int *val) {
  if (div == 1) {
    *val |= 0x00800000;
    return 0;
  }
  if (div == 3) {
    *val |= 0x00900000;
    return 0;
  }
  if (div % 2) return -1;
  if ((div / 2) == 9 || (div / 2) == 10) return -1;
  *val |= ((div / 2 - 1) & 0xf) << 20;
  return 0;
}