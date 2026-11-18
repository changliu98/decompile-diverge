void minmax(int *val, int *n, int *min, int *max) {
  if (*val > *max)
    *max = *val;
  if (*val < *min)
    *min = *val;
}