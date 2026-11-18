double GO_frexp (double x, int *exp)
{
 int n = 0;
 double s = 1.0;

 if (x < 0.0)
 {
  s = -1.0;
  x = -x;
 }

 if (x != 0.0)
 {
  while (x >= 1.0)
  {
   n++;
   x *= 0.5;
  }

  while (x < 0.5)
  {
   n--;
   x *= 2.0;
  }
 }

 *exp = n;
 return s * x;
}