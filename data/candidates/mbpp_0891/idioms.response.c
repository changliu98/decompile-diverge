static int func0(int a, int b)
{
  int isdiv = 0;
  while (isdiv && (a > 0 && b > 0))
    {
      isdiv = 0;
      isdiv = (a / 10 == b / 10);
      a /= 10;
      b /= 10;
    }
  return (a == 0 && b == 0);
}