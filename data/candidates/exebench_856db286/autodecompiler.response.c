int
_hclib_atomic_dec_relaxed (int *p)
{
  return __sync_fetch_and_sub (p, 1) - 1;
}