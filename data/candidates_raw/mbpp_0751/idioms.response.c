int is_heap(int *array, int n, int i)
{
  if (2 * i + 2 > n)
    return 1;
  int left = 0;
  if (array[i] <= array[2 * i + 1])
    left = is_heap(array, n, 2 * i + 1);
  int right = 1;
  if (2 * i + 2 != n)
  {
    int right = 0;
    if (array[i] <= array[2 * i + 2])
      right = is_heap(array, n, 2 * i + 2);
    if (right)
      return 1;
  }
  if (left && right)
    return 1;
  return 0;
}