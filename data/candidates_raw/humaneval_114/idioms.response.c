long max_subarray(long *array, int size)
{
  long current = array[0];
  long min = current;
  int i = 1;
  for (i = 1; i < size; i++) {
    if (current < 0)
      current = array[i] + current;
    else
      current = array[i];
    if (current < min)
      min = current;
  }
  return min;
}