double
frexp(double x, int *eptr)
{
 int exponent;
 double fraction;

 exponent = 0;
 fraction = 1;
 if (x < 0) {
  fraction = -1;
  x = -x;
 }
 if (x != 0) {
  while (x >= 1) {
   x *= 0.5;
   exponent++;
  }
  while (x < 0.5) {
   x *= 2;
   exponent--;
  }
 }
 *eptr = exponent;
 return (x * fraction);
}