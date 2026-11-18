void insert_dle(unsigned char *dst, unsigned char *src, int len) {
  while (len--) {
    *dst++ = *src;
    if (*src++ == DLE) *dst++ = DLE;
  }
}