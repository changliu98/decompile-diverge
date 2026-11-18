int srt1(int n, float *x, int m, float *y, int l, float *l1, int e, float *e1, int g, float *g1, int r, float *r1)
{
  int i;
  float v;
  if (n != m || n != l || n != e || n != g || n != r)
    return 2000;
  for (i = 0; i < n; i++) {
    if (y[i] > x[i])
      v = l1[i];
    else if (y[i] < x[i])
      v = g1[i];
    else
      v = e1[i];
    r1[i] = v;
  }
  return 0;
}