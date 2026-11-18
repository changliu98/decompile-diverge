long xdl_bogosqrt(long n)

{
  long i;
  long n_local;
  
  i = 1;
  for (n_local = n; 0 < n_local; n_local = n_local >> 2) {
    i = i << 1;
  }
  return i;
}