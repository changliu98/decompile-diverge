int func0(int *nums,int size)

{
  int i;
  int sum;
  int size_local;
  int *nums_local;
  
  sum = 0;
  for (i = 0; i < size; i = i + 1) {
    if (nums[i] < 0) {
      sum = nums[i] + sum;
    }
  }
  return sum;
}