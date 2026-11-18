int func0(int n, int k)
{
  int i; int j;
  if (k < n) {
    i = k;
    j = n;
  }
  else {
    i = n;
    j = k;
  }
  return (i * (i + 1) * (i + 2) / 6);
}