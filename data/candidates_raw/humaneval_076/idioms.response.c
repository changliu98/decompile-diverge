int is_prime(int x, int n)
{
  int i = 1;
  int j = 0;
  for (;;) {
    int is_divisible = i <= x && j < 100;
    if (!is_divisible)
      break;
    if (i == x)
      return 1;
    i *= n;
    j++;
  }
  return 0;
}