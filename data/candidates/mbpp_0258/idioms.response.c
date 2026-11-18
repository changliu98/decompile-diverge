int func0(int *array_nums, int n)
{
  int count_odd = 0;
  int i = 0;
  for (i = 0; i < n; i++)
  {
    if (array_nums[i] % 2 == 1)
    {
      count_odd++;
    }
  }
  return (count_odd);
}