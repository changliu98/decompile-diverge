void swap_float_4(float *f) {
  unsigned char *c = (unsigned char *)f;
  unsigned char temp;
  temp = c[0];
  c[0] = c[3];
  c[3] = temp;
  temp = c[1];
  c[1] = c[2];
  c[2] = temp;
}