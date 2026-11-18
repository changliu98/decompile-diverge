void vscale(float *a, float *b, float s) {
  a[0] = b[0] * s;
  a[1] = b[1] * s;
  a[2] = b[2] * s;
}