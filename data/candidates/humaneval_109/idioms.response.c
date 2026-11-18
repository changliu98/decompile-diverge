int func0(int *array, int size)
{
  int i; int count = 0;
  if (size == 0)
    return 1;
  for (i = 1; i < size; i++)
    if (array[i] < array[i - 1])
      count++;
  if (array[size - 1] > array[0])
    count++;
  return count < 2;
}