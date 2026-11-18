int func0(int n) {
  double sqrt_n;
  int i;
  sqrt_n = sqrt((double)n);
  i = (int)floor(sqrt_n);
  return (i + 1) * (i + 1);
}