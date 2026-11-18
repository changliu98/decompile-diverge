static long long t_add(long long a, long long b, int *ok)
{
  int ok1 = 0;
  if (*ok)
  {
    long long max = a > b ? a : b;
    ok1 = a + b >= max;
  }
  *ok = ok1;
  if (*ok)
    return a + b;
  return 0;
}