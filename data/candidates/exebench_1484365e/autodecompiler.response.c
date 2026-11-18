int
atomic32_increment (int *p)
{
  int old = __sync_fetch_and_add (p, 1) + 1;
  return old;
}