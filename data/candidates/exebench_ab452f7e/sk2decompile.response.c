void maxdig(int *n, int *max) {
  if (*n == 0) {
    return *max;
  }
  r = *n % 10;
  if (r >= *max) {
    *max = r;
  }
  *n /= 10;
  maxdig(n, max);
}