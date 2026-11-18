int
_hclib_atomic_dec_release (int *p)
{
  return __sync_fetch_and_sub (p, 1) - 1;
}