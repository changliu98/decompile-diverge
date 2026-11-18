int _log10_int(int n) {
  double ln, l2pi;
  if (n < 0) return 0;
  if (n < 2) return 1;
  ln = log10((double)n / 2.71828182845904523536028747135266250);
  l2pi = log10(6.28318530717958647692528676655900576);
  return (int)floor(n * ln + l2pi / 2.0) + 1;
}