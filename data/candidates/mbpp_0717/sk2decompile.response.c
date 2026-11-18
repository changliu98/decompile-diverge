double func0(double *x, int n) {
  int i;
  double avg, sum;
  if (n < 2) return 0.0;
  avg = avg_calc(x, n);
  sum = 0.0;
  for (i = 0; i < n; i++) {
    sum += (x[i] - avg) * (x[i] - avg);
  }
  return sqrt(sum / (n - 1));
}