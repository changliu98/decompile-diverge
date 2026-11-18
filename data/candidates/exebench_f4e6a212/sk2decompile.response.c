void mix_16h_to_32_s2(unsigned char *dest, unsigned char *src, int len) {
  int *dest_i = (int *)dest;
  short *src_s = (short *)src;
  len >>= 1;
  while (len--) {
    *dest_i++ += *src_s++ >> 1;
    *dest_i++ += *src_s++ >> 1;
    src += 8;
  }
}