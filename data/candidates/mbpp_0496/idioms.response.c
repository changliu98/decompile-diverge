void func0(int *array, int len, int k, int *result)
{
  int i;
  qsort(array, len, sizeof(int), compare);
  for (i = 0; i < k; i++)
    result[i] = array[i];
}