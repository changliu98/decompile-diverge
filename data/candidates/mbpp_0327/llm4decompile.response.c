int func0(int a, int b, int c)
{
  if (a == b)
    return 1;
  if (b == c)
    return 1;
  if (c == a)
    return 1;
  return 0;
}