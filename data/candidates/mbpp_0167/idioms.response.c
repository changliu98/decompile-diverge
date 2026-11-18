int func0(int n)
{
  int i = n;
  int count = 0;
  if (n && (n & (n - 1)) == 0)
    return n;
  while (i) {
    i >>= 1;
    count++;
  }
  return (1 << count);
}