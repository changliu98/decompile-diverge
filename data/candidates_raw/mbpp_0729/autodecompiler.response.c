void add(int *a, int *b, int *c, int n)
{
  int i;
  for (i = 0; ; i = i + 1)
  {
    if (i >= n) break;
    c[i] = a[i] + b[i];
  }
}