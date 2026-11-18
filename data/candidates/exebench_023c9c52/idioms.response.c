int i2s_sf_sclkdiv(int div, int *out)
{
  if (div == 1) {
    *out |= 0x800000;
    return 0;
  }
  if (div == 3) {
    *out |= 0x900000;
    return 0;
  }
  if (div % 2 == 0) {
    int div2 = div / 2;
    if (div2 == 9 || div2 == 10)
      return -1;
    *out |= (div2 - 1) << 20 & 0xf00000;
    return 0;
  }
  return -1;
}