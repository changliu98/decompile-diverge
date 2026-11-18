char *func0(int a, int b, int c)
{
  if (b * b - 4 * a * c > 0)
    return ("2 solutions");
  if (b * b == 4 * a * c)
    return ("1 solution");
  return ("No solutions");
}