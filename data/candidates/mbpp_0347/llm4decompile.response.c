int func0(int m, int n)
{
 if (m > n) {
  int tmp = m;
  m = n;
  n = tmp;
 }

 return (n * (n + 1) * (3 * m - n + 1)) / 6;
}