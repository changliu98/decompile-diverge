float FloatNoSwap(float *f) {
  unsigned char *c = (unsigned char *)f;
  return (float)(c[0] + (c[1] << 8) + (c[2] << 16) + (c[3] << 24));
}