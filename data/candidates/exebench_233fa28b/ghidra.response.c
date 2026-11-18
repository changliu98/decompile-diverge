size_t utf8BytesToCodePoint(char *buf,size_t len,int *cp)

{
  byte bVar1;
  uchar byte;
  int *cp_local;
  size_t len_local;
  char *buf_local;
  
  if (len != 0) {
    bVar1 = *buf;
    if ((bVar1 & 0x80) == 0) {
      *cp = (uint)bVar1;
      return 1;
    }
    if ((bVar1 & 0xe0) == 0xc0) {
      if (1 < len) {
        *cp = ((int)*buf & 0x1fU) << 6 | (int)buf[1] & 0x3fU;
        return 2;
      }
    }
    else if ((bVar1 & 0xf0) == 0xe0) {
      if (2 < len) {
        *cp = ((int)*buf & 0xfU) << 0xc | ((int)buf[1] & 0x3fU) << 6 | (int)buf[2] & 0x3fU;
        return 3;
      }
    }
    else if (((bVar1 & 0xf8) == 0xf0) && (3 < len)) {
      *cp = ((int)*buf & 7U) << 0x12 | ((int)buf[1] & 0x3fU) << 0xc | ((int)buf[2] & 0x3fU) << 6 |
            (int)buf[3] & 0x3fU;
      return 4;
    }
  }
  return 0;
}