int func0(int *array_nums,int size)

{
  int i;
  int count_even;
  int size_local;
  int *array_nums_local;
  
  count_even = 0;
  for (i = 0; i < size; i = i + 1) {
    if (array_nums[i] % 2 == 0) {
      count_even = count_even + 1;
    }
  }
  return count_even;
}