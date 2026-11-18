int func0(int a, int b, int d)
{
 int min = a < b ? a : b;
 int max = a > b ? a : b;

 if (max <= d)
  return (d + max - 1) / max;

 if (d == 0)
  return 0;

 if (d == min)
  return 1;

 return 2;
}