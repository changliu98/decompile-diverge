int func0(int n, int x, int y)
{
 int i;
 int isp;

 isp = 1;
 for (i = 2; i * i <= n; i++) {
  if (n % i == 0) {
   isp = 0;
  }
 }

 if (isp) {
  return x;
 } else {
  return y;
 }
}