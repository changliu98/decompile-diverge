int func0(int n)
{
 int a, b, c, d;
 int i;

 a = 3;
 b = 0;
 c = 2;

 if (n == 0) {
  return 3;
 }

 if (n == 1) {
  return 3;
 }

 if (n == 2) {
  return 5;
 }

 d = 5;
 for (i = n; i >= 3; i--) {
  d = d + a + b;
  a = b;
  b = c;
  c = a + b;
 }

 return d;
}