int func0(int a, int b, int c)
{
  if (a == b)
    return 0;
  if (b == c)
    return 0;
  if (c == a)
    return 0;
  return 1;
}