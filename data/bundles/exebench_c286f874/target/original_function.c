static __inline__
int fetch_and_add(int* p, int i)
{
  return __sync_fetch_and_add(p, i);
}