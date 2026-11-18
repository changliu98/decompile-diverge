void minmax(int *p, int *q, int *min, int *max) {
  if (*p > *max) {
    *max = *p;
  }
  if (*p < *min) {
    *min = *p;
  }
}