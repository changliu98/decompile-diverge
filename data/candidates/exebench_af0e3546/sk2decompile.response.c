void set_mac(unsigned char *dst, unsigned char *src) {
  int i;
  for (i = 0; i < 6; i++) {
    dst[i] = src[i];
  }
}