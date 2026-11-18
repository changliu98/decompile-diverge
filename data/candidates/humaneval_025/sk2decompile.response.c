int *__factor(int n, int *len) {
  int *factors = malloc(256);
  *len = 0;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      n /= i;
      factors[(*len)++] = i;
    }
  }
  if (n > 1) {
    factors[(*len)++] = n;
  }
  return factors;
}