double func0(int n) {
  double sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += i * i * i;
  }
  return round(sum / n * 1000000) / 1000000;
}