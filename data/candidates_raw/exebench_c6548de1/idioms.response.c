void move_to_end(int *a)
{
  int minn = 0;
  int i;
  for (i = 0; i < 10; i++)
    if (a[i] < a[0])
      minn = i;
  int maxn = 0;
  for (i = 0; i < 10; i++)
    if (a[i] > a[0])
      maxn = i;
  a[0] += a[minn];
  a[minn] = a[0] - a[minn];
  a[0] -= a[minn];
  a[9] += a[maxn];
  a[maxn] = a[9] - a[maxn];
  a[9] -= a[maxn];
}