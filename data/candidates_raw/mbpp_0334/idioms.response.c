int isTriangle(int a, int b, int c)
{
  if (a + b > c && a + c > b && b + c > a)
    return 1;
  return 0;
}