int func0(int *array, int size, int min, int max)
{
  int count = 0;
  for (int i = 0; i < size; i++)
  {
    if (array[i] >= min && array[i] <= max)
    {
      count++;
    }
  }
  return count;
}