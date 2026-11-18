int func0(int n) {
  int i, j, is_prime, count;
  count = 0;
  for (i = 0; i < n; i++) {
    if (i > 1) {
      is_prime = 1;
      for (j = 2; j < i; j++) {
        if (i % j == 0) {
          is_prime = 0;
          break;
        }
      }
      if (is_prime) {
        count++;
      }
    }
  }
  return count;
}