void sort(int *array, int n, int *sorted)
{
  qsort(array, n, sizeof(int), cmpfunc);
  for (int i = 0; i < n; i++)
  {
    sorted[i] = array[i];
  }
  return;
}