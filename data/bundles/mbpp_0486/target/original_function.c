double func0(int n, int r, double p) {
  int r0 = r;
  if (r > n / 2) r = n - r;
  double answer = 1.0;
  for (int i = 1; i <= r; i++) {
    answer *= (n - r + i);
    answer /= i;
  }
  return answer * pow(p, r0) * pow(1 - p, n - r0);
}