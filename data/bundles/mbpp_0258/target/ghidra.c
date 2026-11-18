int func0(int *array_nums,int n)

{
  int i;
  int count_odd;
  int n_local;
  int *array_nums_local;
  
  count_odd = 0;
  for (i = 0; i < n; i = i + 1) {
    if (array_nums[i] % 2 != 0) {
      count_odd = count_odd + 1;
    }
  }
  return count_odd;
}