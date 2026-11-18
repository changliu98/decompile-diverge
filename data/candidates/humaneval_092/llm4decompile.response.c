int func0(float a, float b, float c)
{
  if (roundf(a) != a)
    return 0;
  if (roundf(b) != b)
    return 0;
  if (roundf(c) != c)
    return 0;
  if (a + b == c)
    return 1;
  if (a + c == b)
    return 1;
  if (b + c == a)
    return 1;
  return 0;
}