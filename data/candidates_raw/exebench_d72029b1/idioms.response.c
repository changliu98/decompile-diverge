void clear(short n, int *a)
{
  short i;
  for (i = 0; i < n; i++)
    a[i + 1] = 0;
}