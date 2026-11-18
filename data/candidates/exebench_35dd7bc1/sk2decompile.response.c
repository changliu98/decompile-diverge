static int i2s_sf_mclkdiv(unsigned int mclkdiv, unsigned int *sf_reg) {
  int ret;
  if (mclkdiv == 1) {
    *sf_reg |= 0x14000000;
    ret = 0;
  } else if (mclkdiv == 3) {
    *sf_reg |= 0x13000000;
    ret = 0;
  } else if (mclkdiv == 5) {
    *sf_reg |= 0x12000000;
    ret = 0;
  } else if (mclkdiv == 14) {
    *sf_reg |= 0x0e000000;
    ret = 0;
  } else if (mclkdiv % 2) {
    ret = -1;
  } else {
    mclkdiv /= 2;
    if (mclkdiv == 21 || mclkdiv == 20 || mclkdiv == 19 || mclkdiv == 15) {
      ret = -1;
    } else {
      *sf_reg |= ((mclkdiv - 1) & 0x1f) << 24;
      ret = 0;
    }
  }
  return ret;
}