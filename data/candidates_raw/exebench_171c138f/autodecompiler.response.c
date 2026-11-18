int
foo (int *p)
{
  int old = 1;
  return __sync_fetch_and_add (p, old);
}