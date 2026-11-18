int max_subarray(int *array, int n)
{
  int i; int j; int k;
  int *newarray;
  int max = 0;
  newarray = (int *) ( ( (int *) (array) ) - ( ( ( (unsigned long) (n) * (sizeof(int)) ) + (sizeof(int) - 1) ) & ~( (sizeof(int) - 1) ) ) );
  for (i = 0; i < n; i++)
    newarray[i] = array[i];
  for (i = 1; i < n; i++)
  {
    for (j = 0; j < i; j++)
    {
      if (array[i] > array[j] && newarray[i] < newarray[j] + array[i])
        newarray[i] = newarray[j] + array[i];
    }
  }
  for (k = 0; k < n; k++)
  {
    if (newarray[k] > max)
      max = newarray[k];
  }
  return (max);
}