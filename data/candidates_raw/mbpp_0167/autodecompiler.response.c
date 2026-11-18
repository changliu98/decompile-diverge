int ispow2(int n)
{
 int k = 0, p;

 if ((n & (n - 1)) == 0) {
  for (p = n; p != 0; p >>= 1, k++);
  return (1 << k);
 }
}