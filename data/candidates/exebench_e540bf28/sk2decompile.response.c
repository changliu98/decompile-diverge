void rfft1pt(float *a) {
  float t1, t2;
  t1 = a[0];
  t2 = a[1];
  a[0] = t1 + t2;
  a[1] = t1 - t2;
}