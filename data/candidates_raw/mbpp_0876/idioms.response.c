int lcm(int a, int b)
{
  int c = a > b ? a : b;
  while (c % a || c % b)
    ++c;
  return c;
}