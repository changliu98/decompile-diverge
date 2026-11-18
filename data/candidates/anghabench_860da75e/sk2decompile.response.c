double rel_stddev_stats(double stddev, double mean) {
  double rel_stddev = 0.0;
  if (mean != 0.0) {
    rel_stddev = 100.0 * stddev / mean;
  }
  return rel_stddev;
}