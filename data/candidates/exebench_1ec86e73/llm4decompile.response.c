double
frexp(double x, int *exp)
{
 int sign;
 double sig;
 int e;

 sign = 1;
 if (x < 0.0) {
  sign = -1;
  x = -x;
 }

 *exp = 0;
 e = 1;
 sig = x;
 while (sig < (double)0.5 || sig >= 1.0) {
  e *= 2;
  *exp += 1;
  sig = x / e;
 }

 return sign * sig;
}