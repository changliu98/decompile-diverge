int foo(int x, int y, int z, int w)
{
  int t = x + y;
  int res;
  if ((t >= z) && (t <= w))
    res = 20;
  else
    res = t;
  return res;
}