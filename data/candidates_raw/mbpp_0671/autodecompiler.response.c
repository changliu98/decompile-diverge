int next_power(int n)
{
 int m;
 int p;

 if (n == 0) {
  m = 1;
 } else if ((n & (n + 1)) == 0) {
  m = n;
 } else {
  p = (int) (log2((double) (n ^ (n - 1))) + 1);
  m = n | (1 << (p - 1));
 }

 return m;
}