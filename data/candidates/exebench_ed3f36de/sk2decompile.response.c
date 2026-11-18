void test_mean2(double *mean, double *data, int n) {
  int i;
  double sum1 = 0.0;
  double sum2 = 0.0;
  for (i = 0; i < 2 * n; i += 2) {
    sum1 += data[i];
  }
  for (i = 0; i < 2 * n; i += 2) {
    sum2 += data[i + 1];
  }
  mean[0] = sum1 / (double)n;
  mean[1] = sum2 / (double)n;
}