void sseround(float *x) {
  int *y = (int *)x;
  y[0] = y[0] & 0x7fffffff;
  y[1] = y[1] & 0x7fffffff;
  y[2] = y[2] & 0x7fffffff;
  y[3] = y[3] & 0x7fffffff;
}