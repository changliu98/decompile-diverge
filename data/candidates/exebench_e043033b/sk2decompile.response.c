void adjust_interval(double *interval, int n) {
  double ratio;
  ratio = (double)n / *interval;
  if (ratio < 5.0) {
    *interval = 0.2;
  }
}