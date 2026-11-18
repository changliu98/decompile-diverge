void GetLims(double *x, double x1, double x2, int n, int *i1, int *i2) {
  int i;
  int found1 = 0;
  int found2 = 0;
  double xi;
  if (n == 0) {
    *i1 = 0;
    *i2 = -1;
    return;
  }
  for (i = 0; i < n; i++) {
    xi = x[i];
    if (found1 == 0 && xi >= x2) {
      *i1 = 0;
      *i2 = -1;
      found1 = 1;
      found2 = 1;
    } else if (found1 == 0 && xi >= x1) {
      *i1 = i;
      found1 = 1;
    } else if (found2 == 0 && xi >= x2) {
      *i2 = i - 1;
      found2 = 1;
    }
  }
  if (found1 == 0) {
    *i1 = 0;
    *i2 = -1;
  } else if (found2 == 0) {
    *i2 = n - 1;
  }
}