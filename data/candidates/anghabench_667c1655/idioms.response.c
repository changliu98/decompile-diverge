static long xdl_bogosqrt(long n)
{
  long a = 1;
  while (n > 0) {
    a = a << 1;
    n = n >> 2;
  }
  return a;
}