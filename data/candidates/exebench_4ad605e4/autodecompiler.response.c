int
atmc_fetch_and_add (volatile int* x, int y)
{
  int old = y;
  y = __sync_fetch_and_add (x, y);
  return old + y;
}