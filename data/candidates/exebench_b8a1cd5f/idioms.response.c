int atomic32_decrement(int *ptr)
{
  return __sync_sub_and_fetch(ptr, 1);
}