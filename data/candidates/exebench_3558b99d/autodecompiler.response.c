long
ff_atomic_dec_long (long *ptr, long value)
{
  return __sync_fetch_and_add (ptr, -value);
}