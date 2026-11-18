int
atomic_add(int *x, int y)
{
  int tmp = __sync_fetch_and_add(x, y);
  return tmp + y;
}