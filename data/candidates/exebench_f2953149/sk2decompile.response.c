void numpar(double *x, int *n, int *p) {
  int i = -1, j = 0, k = 0;
  int dup[*n];
  int dup_count = -1;
  double diff = 0.0;
  while (i < *n - 1) {
    i++;
    for (j = 0; j < dup_count; j++) {
      if (i == dup[j]) {
        i++;
      }
    }
    for (k = i + 1; k < *n; k++) {
      for (j = 0; j < dup_count; j++) {
        if (k == dup[j]) {
          k++;
        }
      }
      diff = x[i] - x[k];
      if (diff < 0) {
        diff *= -1;
      }
      if (diff == 0) {
        dup_count++;
        dup[dup_count] = k;
        *p -= 1;
      }
    }
  }
}