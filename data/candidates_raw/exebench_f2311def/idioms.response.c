int findmax(float *array, int i, int j)
{
  int k; int max = i;
  for (k = i + 1; k <= j; k++)
    if (array[k] > array[max])
      max = k;
  return max;
}