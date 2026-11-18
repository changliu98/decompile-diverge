double frexp(double x, int *exp)
{
 int i = 0;
 double sign = 1;

 if (x < 0) {
  x = -x;
  sign = -1;
 }

 if (x == 0) {
  *exp = 0;
  return sign * x;
 }

 while (x >= 1)
  x /= 2, i++;

 while (x < .5)
  x *= 2, i--;

 *exp = i;
 return sign * x;
}