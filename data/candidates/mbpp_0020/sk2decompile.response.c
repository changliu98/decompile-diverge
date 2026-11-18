bool _is_prime(long n) {
  if (n % 2 == 0) return false;
  if (n == 1) return true;
  long m = n + 1;
  long i = 0;
  while (m % 2 == 0) {
    m /= 2;
    i++;
    if (i == m) return true;
  }
  return false;
}