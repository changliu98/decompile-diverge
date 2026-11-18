int int2bin(int n, int *binary)
{
  int i = n;
  unsigned int j = 1;
  int k = 0;
  int l;
  while (j <= n)
  {
    j = (j * 2);
    k++;
  }
  j = (j / 2);
  k--;
  for (l = k; l >= 0; l--)
  {
    if (i - j >= 0)
    {
      i = i - j;
      binary[k - l] = 1;
    }
    else
    {
      binary[k - l] = 0;
    }
    j = (j / 2);
  }
  return (k);
}