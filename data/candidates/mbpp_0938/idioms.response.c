void func0(int *a, int *b, int *c, int p, int q, int r, int *res)
{
  int min = 0x7fffffff; int max = 0;
  int i = 0; int j = 0; int k = 0;
  int min1; int min2; int max1; int max2;
  while (1)
  {
    int valid = (i < p && j < q && k < r);
    if (!valid)
      break;
    if (a[i] < b[j])
    {
      min1 = (a[i] < c[k]) ? a[i] : c[k];
      min2 = min1;
    }
    else
    {
      min1 = (b[j] < c[k]) ? b[j] : c[k];
      min2 = min1;
    }
    if (a[i] > b[j])
    {
      max1 = (a[i] > c[k]) ? a[i] : c[k];
      max2 = max1;
    }
    else
    {
      max1 = (b[j] > c[k]) ? b[j] : c[k];
      max2 = max1;
    }
    if (max2 - min2 < min)
    {
      i0 = i;
      j0 = j;
      k0 = k;
      min = max2 - min2;
    }
    if (min == 0)
      break;
    if (a[i] == min2)
      i++;
    else if (b[j] == min2)
      j++;
    else
      k++;
  }
  res[0] = a[i0];
  res[1] = b[j0];
  res[2] = c[k0];
}