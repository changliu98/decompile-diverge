int func0(int n) {
  if (n <= 3) return n;
  int min = n;
  for (int i = 1; i <= n; i++) {
    int square = i * i;
    if (square > n) break;
    min = min < func0(n - square) + 1 ? min : func0(n - square) + 1;
  }
  return min;
}