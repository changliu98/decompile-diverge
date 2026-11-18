int __cdecl func0(int *array_nums, int size)
{
  int count_even = 0;

  for (int i = 0; i < size; ++i)
  {
    if (array_nums[i] % 2 == 0)
      ++count_even;
  }
  
  return count_even;
}