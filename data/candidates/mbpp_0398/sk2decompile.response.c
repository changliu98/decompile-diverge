int func0(int* a, int n) {
  int x, i, sum;
  sum = 0;
  for (i = 0; i < n; i++) {
    x = a[i];
    if (x < 0) x = -x;
    while (x > 0) {
      sum += x % 10;
      x /= 10;
    }
  }
  return sum;
}