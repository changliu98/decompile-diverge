int transF(int m, int n, float a[], int p, int q, float b[])
{
  int i; int j;
  if (m != q || n != p)
    return (2000);
  for (i = 0; i < p; i++)
    for (j = 0; j < q; j++)
      b[i + q * j] = a[j + n * i];
  return (0);
}