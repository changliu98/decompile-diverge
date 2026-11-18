int func0(int *a, int n) {
  int x, is_prime, i, max, j;
  j = 0;
  max = 0;
  for (i = 0; i < n; i++) {
    x = a[i];
    if (x > 1) {
      is_prime = 1;
      for (j = 2; j * j <= x; j++) {
        if (x % j == 0) {
          is_prime = 0;
          break;
        }
      }
      if (is_prime) {
        max = (x > max) ? a[i] : max;
      }
    }
  }
  while (max > 0) {
    max += max % 10;
    max /= 10;
  }
  return max;
}