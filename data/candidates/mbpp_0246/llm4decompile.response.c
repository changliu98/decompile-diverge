double func0(double number)
{
 double x, y;

 if (number == 0.0)
  return 0.0;

 x = number / 2.0;
 y = x + 1.0;

 while (x != y || x != x || y != y) {
  x = (x + number / x) / 2.0;
  y = x;
 }

 return x;
}