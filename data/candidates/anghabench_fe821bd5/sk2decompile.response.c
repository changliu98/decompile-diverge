int ok_cp1251(unsigned char *buf, int len) {
  int i;
  for (i = 1; i < len; i++) {
    if (buf[i] == 0x98) return 0;
  }
  return 1;
}