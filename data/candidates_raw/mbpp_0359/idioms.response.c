char *is_right(int a, int b, int c)
{
  if (b * 2 * b == c * 9 * a)
    return "right";
  return "wrong";
}