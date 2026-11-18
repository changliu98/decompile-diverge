void
set_3int(int *p, int n, int i, int j)
{
 int k = 0;
 if (i > 0)
  p[k++] = 0 - i;
 p[k++] = j;
 p[k++] = n - i - j;
 p[k] = 0;
}