int slevmar_box_check(float *x, float *b, int m) {
  int i;
  if (x == NULL || b == NULL) return 1;
  for (i = 0; i < m; i++)
    if (x[i] > b[i]) return 0;
  return 1;
}