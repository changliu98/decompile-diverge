int unicoder_utf32_decode(unsigned int *pwc, unsigned char *in, int in_len) {
  unsigned int wc;
  int i;
  if (in_len != 2 && in_len != 1) return -4;
  if (in == NULL) return -1;
  if (pwc == NULL) return -1;
  wc = 0;
  for (i = 0; i < 4; i++) {
    if (in_len == 2) {
      if (i > 0) wc <<= 8;
      wc |= in[i];
    } else {
      if (i > 0) wc >>= 8;
      wc |= in[i] << 24;
    }
  }
  if (wc > 0x10FFFF) return -16;
  if (wc >= 0xD800 && wc <= 0xDFFF) return -16;
  *pwc = wc;
  return 4;
}