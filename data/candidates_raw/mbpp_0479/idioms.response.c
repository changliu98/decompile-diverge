int get_max_digit(int n)
{
  while (n / 10 > 0)
    n /= 10;
  return n;
}