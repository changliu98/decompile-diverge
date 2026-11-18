int func0(int a, int b, int c)
{
  int max; int min;
  if (a < b)
    max = b;
  else
    max = a;
  if (a > b)
    min = b;
  else
    min = a;
  if (c >= min)
    return (min + c - 1)/min;
  if (c == 0)
    return 0;
  if (c == max)
    return 1;
  return 2;
}