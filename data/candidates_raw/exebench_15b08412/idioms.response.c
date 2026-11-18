int idiv64(unsigned long long *a, unsigned long long b)
{
  if (b == 0 || a[1] >= b)
    return 1;
  unsigned long long t = *a;
  *a = t / b;
  a[1] = t % b;
  return 0;
}