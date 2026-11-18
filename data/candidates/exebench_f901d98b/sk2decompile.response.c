void pwm(double *freq, int n, double shift1, double shift2, double *pwm,
         int type) {
  int i;
  double mean = 0.0;
  double var = 0.0;
  double skew = 0.0;
  double x;
  if (shift1 == 0.0 && shift2 == 0.0) {
    for (i = 1; i <= n; i++) {
      mean += freq[i - 1];
      if (type == 0) {
        var += (n - i) * freq[i - 1];
        skew += (n - i) * (n - i - 1) * freq[i - 1];
      }
      if (type == 1) {
        var += (i - 1) * freq[i - 1];
        skew += (i - 1) * (i - 2) * freq[i - 1];
      }
    }
  } else {
    for (i = 1; i <= n; i++) {
      mean += freq[i - 1];
      x = (i + shift1) / (n + shift2);
      if (type == 0) {
        var += (1.0 - x) * freq[i - 1];
        skew += (1.0 - x) * (1.0 - x) * freq[i - 1];
      }
      if (type == 1) {
        var += x * freq[i - 1];
        skew += x * x * freq[i - 1];
      }
    }
  }
  pwm[0] = mean / n;
  pwm[1] = var / n / (n - 1);
  pwm[2] = skew / n / ((n - 1) * (n - 2));
}