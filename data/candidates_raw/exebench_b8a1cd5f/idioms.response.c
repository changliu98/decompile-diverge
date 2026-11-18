int xfree(int *ptr)
{
  return __sync_sub_and_fetch(ptr, 1);
}