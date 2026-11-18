int INDMAXVAL(float *x, int start, int end) {
  int i, ind;
  ind = start;
  for (i = start + 1; i <= end; i++) {
    if (x[i] > x[ind]) ind = i;
  }
  return ind;
}