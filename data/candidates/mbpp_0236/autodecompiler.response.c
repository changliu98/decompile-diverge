int func0(int i, int j)
{
 int t1, t2, n;
 if (i < j) {
  n = -1;
 }
 else {
  t1 = ((i - j + 1) * (i - j + 2)) / 2;
  t2 = ((i - 2 * j + 1) * (i - 2 * j + 2)) / 2;
  n = t1 + t2;
 }
 return n;
}