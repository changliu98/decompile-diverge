int
atomic_dec (int *ptr)
{
  return __sync_fetch_and_add (ptr, -1);
}