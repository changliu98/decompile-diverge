int sum(int *array, int size)
{
  int sum = 0;
  int i = 0;
  for (i = 0; i < size; i++)
    sum += array[i];
  return (sum);
}