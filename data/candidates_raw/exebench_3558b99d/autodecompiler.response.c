long
__sync_fetch_and_sub_8 (long *ptr, long value)
{
  return __sync_fetch_and_add (ptr, -value);
}