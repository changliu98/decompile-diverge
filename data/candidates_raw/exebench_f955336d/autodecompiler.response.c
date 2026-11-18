int
__sync_fetch_and_add_4 (int *ptr, int val)
{
  return __atomic_fetch_add_4 (ptr, val, 5);
}