void _power(int* x, int n, int p, int* y) {
  int i;
  for (i = 0; i < n; i++) {
    y[i] = (int)pow((double)x[i], (double)p);
  }
}