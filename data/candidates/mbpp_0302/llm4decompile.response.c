int func0(int n)
{
  int msb;

  if (n == 0)
    return 0;

  msb = 0;
  while ((n /= 2) > 0)
    msb++;

  return 1 << msb;
}