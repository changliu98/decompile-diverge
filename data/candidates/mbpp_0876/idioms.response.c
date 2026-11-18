int func0(int a, int b)
{
  int c = a > b ? a : b;
  while (c % a || c % b)
    ++c;
  return c;
}