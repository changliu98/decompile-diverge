double func0(int n) {
  int i;
  double sum = 0.0;
  for (i = 1; i <= n; i++) {
    sum += i * i * i;
  }
  sum /= n;
  sum = round(sum * 1000000) / 1000000;
  return sum;
}