int maxdig(int *n, int *max)
{
  int maxdig_dig;
  if (*n == 0)
    return *max;
  maxdig_dig = *n % 10;
  if (maxdig_dig >= *max)
    *max = maxdig_dig;
  *n = *n / 10;
  return maxdig(n, max);
}