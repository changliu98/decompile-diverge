int
foo(int *p)
{
  int n = 0xdead;

  *p = n;

  return *p;
}