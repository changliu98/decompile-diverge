int is_sorted(float *array, int size)
{
  int decr = 0;
  int incr = 0;
  int i;
  for (i = 1; i < size; i++)
  {
    if (array[i] > array[i - 1])
      incr = 1;
    if (array[i - 1] > array[i])
      decr = 1;
  }
  if (decr + incr == 2)
    return 0;
  return 1;
}