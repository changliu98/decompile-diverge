int func0(int *array, int n)
{
  int i; int j;
  int *up = array;
  int *down = array + n;
  int *len = down + 1;
  int max = 0;
  for (i = 0; i <= n; i++)
    len[i] = 1;
  for (i = 1; i < n; i++)
    for (j = 0; j < i; j++)
      if (up[i] > up[j] && len[i] < len[j] + 1)
        len[i] = len[j] + 1;
  for (i = 0; i <= n; i++)
    len[i] = 1;
  for (i = n - 1; i >= 0; i--)
    for (j = n - 1; j > i; j--)
      if (up[i] > up[j] && len[i] < len[j] + 1)
        len[i] = len[j] + 1;
  max = len[0] + len[n] - 1;
  for (i = 1; i < n; i++)
    if (len[i] + len[i] - 1 > max)
      max = len[i] + len[i] - 1;
  return max;
}