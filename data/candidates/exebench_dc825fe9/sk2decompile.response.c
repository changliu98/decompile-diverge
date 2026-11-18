void summary(int *a, int n, double *ppos, double *nneg, double *zeros) {
  int i, pos = 0, neg = 0, zero = 0;
  for (i = 0; i < n; i++) {
    if (a[i] > 0)
      pos++;
    else if (a[i] < 0)
      neg++;
    else
      zero++;
  }
  *ppos = (double)pos / n;
  *nneg = (double)neg / n;
  *zeros = (double)zero / n;
}