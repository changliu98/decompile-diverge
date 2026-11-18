int func0(int m, int n)
{
 if (m > n) {
  int tmp = m;
  m = n;
  n = tmp;
 }

 return m * (m + 1) * (2 * m + 1) / 6
     + m * (m + 1) * (n - m) / 2;
}