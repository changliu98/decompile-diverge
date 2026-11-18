int count_even(int *array_nums, int size)
{
  int count_even = 0;
  int i = 0;
  for (i = 0; i < size; i++)
  {
    if (array_nums[i] % 2 == 0)
    {
      count_even++;
    }
  }
  return (count_even);
}