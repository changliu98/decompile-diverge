int condF(int n, float *x, int x_offset, float *y, int y_offset, float *z,
          int z_offset, float *a, int a_offset, float *b, int b_offset,
          float *c) {
  int i;
  float val;
  if (n != x_offset || n != y_offset || n != z_offset || n != a_offset ||
      n != b_offset)
    return 2000;
  for (i = 0; i < n; i++) {
    if (x[i] < y[i])
      val = z[i];
    else if (x[i] > y[i])
      val = b[i];
    else
      val = a[i];
    c[i] = val;
  }
  return 0;
}