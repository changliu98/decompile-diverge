void adjust_interval(double *interval, int test_length) {
  int min_samples = 100;
  if ((double) test_length / *interval < min_samples) {
    *interval = (double) test_length / min_samples;
  }
}