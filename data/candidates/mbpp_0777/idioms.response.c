int func0(int *array, int n)
{
  int sum; int i;
  qsort(array, n, sizeof(int), compare);
  sum = array[0];
  for (i = 0; i < n - 1; i++)
  {
    if (array[i] != array[i + 1])
    {
      sum += array[i + 1];
    }
  }
  return (sum);
}