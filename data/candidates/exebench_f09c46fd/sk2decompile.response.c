void minmax(int *p, int n, int *min, int *max) {
  if (*p < *min) {
    *min = *p;
  }
  if (*p > *max) {
    *max = *p;
  }
}