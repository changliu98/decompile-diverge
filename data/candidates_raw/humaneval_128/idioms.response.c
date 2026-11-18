int sum_of_abs(int *array, int array_size)
{
  int sum = 0;
  int prods = 1;
  int i;
  if (array_size == 0)
    return -32768;
  for (i = 0; i < array_size; i++)
  {
    sum += abs(array[i]);
    if (array[i] == 0)
      prods = 0;
    if (array[i] < 0)
      prods = -prods;
  }
  return (prods * sum);
}