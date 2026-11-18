int
test_01 (volatile int* x, int y)
{
  return __sync_fetch_and_sub (x, -y);
}