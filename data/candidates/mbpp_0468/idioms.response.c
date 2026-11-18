int func0(int *array, int n)
{
  int i; int j;
  int *arr = array;
  int *max = (int *) ( ( ( (sizeof(int) * (n) + sizeof(int) - 1) / sizeof(int) ) * sizeof(int) ) + (char *) ( &n ) );
  int maxval;
  for (i = 0; i < n; i++)
    max[i] = arr[i];
  for (i = 1; i < n; i++)
    for (j = 0; j < i; j++)
      if (arr[i] > arr[j])
        if (max[i] < (max[j] * arr[i]))
          max[i] = (max[j] * arr[i]);
  maxval = max[0];
  for (i = 1; i < n; i++)
    if (maxval < max[i])
      maxval = max[i];
  return (maxval);
}