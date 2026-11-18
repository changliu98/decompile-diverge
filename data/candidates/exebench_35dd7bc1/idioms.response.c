int i2s_sf_mclkdiv(int div, int *op)
{
  int ret;
  switch (div) {
  case 1:
    *op |= (1 << 24);
    ret = 0;
    break;
  case 3:
    *op |= (3 << 24);
    ret = 0;
    break;
  case 5:
    *op |= (2 << 24);
    ret = 0;
    break;
  case 14:
    *op |= (14 << 20);
    ret = 0;
    break;
  default:
    if (div % 2 == 0) {
      if (div / 2 == 21 || div / 2 == 20 || div / 2 == 19
   || div / 2 == 15)
        ret = -1;
      else {
        *op |= (div / 2 - 1) << 24;
        ret = 0;
      }
    } else {
      ret = -1;
    }
    break;
  }
  return ret;
}