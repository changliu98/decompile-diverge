__attribute__((noinline)) unsigned long
div10quickm (unsigned long *n)
{
  unsigned long q, r, t;

  t = *n;
  q = (t >> 1) + (t >> 2);
  q = q + (q >> 4);
  q = q + (q >> 8);
  q = q + (q >> 16);
  q = q >> 3;
  r = t - (((q << 2) + q) << 1);
  t = q + (r >> 9);
  *n = t;
  t = t << 1;
  t = (t << 2) + t;
  return *n - t;
}