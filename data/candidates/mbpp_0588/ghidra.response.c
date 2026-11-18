int func0(int *nums,int size)

{
  int i;
  int min_val;
  int max_val;
  int size_local;
  int *nums_local;
  
  max_val = -0x80000000;
  min_val = 0x7fffffff;
  for (i = 0; i < size; i = i + 1) {
    if (max_val < nums[i]) {
      max_val = nums[i];
    }
    if (nums[i] < min_val) {
      min_val = nums[i];
    }
  }
  return max_val - min_val;
}