int nextprime(int n)
{
  int i = n;
  int j;
  int factors[100];
  int factor_count;
  int number;
  if (n < 3)
    return n;
  i = i * 2;
  factor_count = 0;
  for (number = i; number > 1; number--) {
    if (number * 2 > i)
      factors[factor_count++] = number;
  }
  for (;;) {
    for (j = 0; j < factor_count; j++) {
      if (i % factors[j]) {
        i += n;
        break;
      }
      if (j == factor_count - 1 && i % factors[j] == 0)
        return i;
    }
  }
}