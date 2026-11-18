long xdl_bogosqrt(long n) {
  long r = 1;
  while (n > 0) {
    r <<= 1;
    n >>= 2;
  }
  return r;
}