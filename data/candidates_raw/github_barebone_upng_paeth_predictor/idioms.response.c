int min3(int a, int b, int c)
{
  int a1 = a + b - c;
  int a2; int a3; int a4;
  if (a1 > a)
    a2 = c - b;
  else
    a2 = b - c;
  if (a1 > b)
    a3 = c - a;
  else
    a3 = a - c;
  if (a1 > c)
    a4 = c - a1;
  else
    a4 = a1 - c;
  if (a2 <= a3 && a2 <= a4)
    return a;
  if (a3 > a4)
    return c;
  return b;
}