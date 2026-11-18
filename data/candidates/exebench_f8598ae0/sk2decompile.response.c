int find(float x, float *xv, int n) {
  int nn, i1, i2;
  if (x <= xv[0]) return 0;
  if (x >= xv[n - 1]) return n - 1;
  i1 = 1;
  i2 = n;
  nn = i2 - i1;
  while (nn > 1) {
    if (x >= xv[(i1 + i2) / 2 - 1])
      i1 = (i1 + i2) / 2;
    else
      i2 = (i1 + i2) / 2;
    nn = i2 - i1;
  }
  return i1 - 1;
}