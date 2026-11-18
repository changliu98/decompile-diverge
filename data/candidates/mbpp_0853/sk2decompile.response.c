int _phi(int n) {
  int result = 1;
  while (n % 2 == 0) {
    n /= 2;
  }
  for (int i = 3; i <= sqrt((double)n) + 1; i += 2) {
    int power = 0;
    int p = 1;
    int p_to_i = 1;
    while (n % i == 0) {
      power++;
      n /= i;
      p_to_i *= i;
      p += p_to_i;
    }
    result *= p;
  }
  if (n > 1) {
    result *= (n + 1);
  }
  return result;
}