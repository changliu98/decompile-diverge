double func0(int n)
{
 double y;

 if (n < 3)
  y = 1;
 else
  y = 1.0 / n + func0(n - 1);

 return y;
}