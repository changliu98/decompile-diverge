int
__sync_fetch_and_sub (int *ptr)
{
  return __sync_fetch_and_add (ptr, -1);
}