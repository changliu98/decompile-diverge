int _largest_prime_factor(int n) {
  int largest_prime_factor = -1;
  while (n % 2 == 0) {
    largest_prime_factor = 2;
    n /= 2;
  }
  int i;
  for (i = 3; i <= sqrt((double)n); i += 2) {
    while (n % i == 0) {
      largest_prime_factor = i;
      n /= i;
    }
  }
  if (n > 2) {
    largest_prime_factor = n;
  }
  return largest_prime_factor;
}