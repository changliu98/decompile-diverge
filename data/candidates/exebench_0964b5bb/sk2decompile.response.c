void bernoulli(int n, int *p, int *q) {
  *p = 0;
  *q = 0;
  if (n == 0) {
    *p = 1;
    *q = 1;
  }
}