static void poly1305_squeeze(unsigned char *dst, unsigned long *s) {
  unsigned long t = 0;
  unsigned int i;
  for (i = 0; i < 16; i++) {
    t += s[i];
    dst[i] = t & 0xff;
    t >>= 8;
  }
  t += s[16];
  dst[16] = t & 3;
  t = (t >> 2) * 5;
  for (i = 0; i < 16; i++) {
    t += dst[i];
    dst[i] = t & 0xff;
    t >>= 8;
  }
  dst[16] += t;
}