int func0(int a, int b)
{
  if (b < 0)
    return -func0(a, -b);
  if (b == 0)
    return 0;
  if (b == 1)
    return a;
  return func0(a, b - 1) + a;
}