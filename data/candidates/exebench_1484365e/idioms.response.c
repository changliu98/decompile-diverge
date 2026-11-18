int atomic32_increment(int *v)
{
  return __sync_fetch_and_add(v, 1);
}