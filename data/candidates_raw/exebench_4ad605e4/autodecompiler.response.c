int
test_02 (volatile int* x, int y)
{
  int old = y;
  y = __sync_fetch_and_add (x, y);
  return old + y;
}