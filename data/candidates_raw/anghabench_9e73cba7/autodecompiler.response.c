int
test_02 (volatile int* x)
{
  return (*x == (int) x) & ((int) (char) 1);
}