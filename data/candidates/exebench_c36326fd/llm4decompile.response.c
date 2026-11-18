void initialize_temp(int *a, int *t)
{
 int i, j;
 for (i = 9, j = 14; i >= 0; i--, j--)
  t[j] = a[i];
 for (; j >= 0; j--)
  t[j] = 0;
}