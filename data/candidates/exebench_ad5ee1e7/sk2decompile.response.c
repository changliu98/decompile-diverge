void cross2(float *a, float *b) {
  float t;
  t = a[0];
  b[0] = -a[1];
  b[1] = t;
}