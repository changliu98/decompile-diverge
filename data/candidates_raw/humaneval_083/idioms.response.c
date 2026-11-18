int get_ten(int n)
{
  int i; int out;
  if (n < 1)
    return 0;
  if (n == 1)
    return 1;
  out = 10 * 2;
  for (i = 2; i < n; i++)
    out *= 10;
  return out;
}