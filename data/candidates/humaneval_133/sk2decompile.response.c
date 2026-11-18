int _sum_of_squares(float *x, int n) {
  int i, sum = 0;
  for (i = 0; i < n; i++) {
    int v = (int)ceil(x[i]);
    sum += v * v;
  }
  return sum;
}