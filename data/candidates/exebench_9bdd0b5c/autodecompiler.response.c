int
foo (int *x)
{
  int y = 0xdead;
  *x = y;
  return *x;
}