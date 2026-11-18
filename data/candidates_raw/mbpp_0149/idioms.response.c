int lis(int *array, int n)
{
  int *length = (int *) ( (int *) (length) - ( ( (sizeof(int) * (n) + sizeof(int) - 1) / sizeof(int) ) * (sizeof(int)) ) );
  int i; int j;
  for (i = 0; i < n; i++)
    length[i] = 1;
  for (i = 0; i < n; i++)
    for (j = 0; j < i; j++)
      if ((array[i] == array[j] + 1 || array[i] == array[j] - 1)
        && length[i] < length[j] + 1)
        length[i] = length[j] + 1;
  int max = 1;
  for (i = 0; i < n; i++)
    if (max < length[i])
      max = length[i];
  return max;
}