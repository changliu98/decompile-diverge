int
foo (int *p)
{
  int old = __sync_fetch_and_sub (p, 1);
  return old - 1;
}