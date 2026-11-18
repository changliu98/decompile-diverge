int maxdig(int *n, int *max)
{
  int ret;
  static int maxdig_dig;
  if (*n == 0)
    ret = *max;
  else
    {
      maxdig_dig = *n % 10;
      if (maxdig_dig >= *max)
 *max = maxdig_dig;

      *n /= 10;
      maxdig(n, max);
    }
  return ret;
}