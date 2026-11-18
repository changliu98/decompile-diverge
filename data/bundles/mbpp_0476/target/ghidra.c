int func0(int *nums,int size)

{
  int i;
  int min_num;
  int max_num;
  int size_local;
  int *nums_local;
  
  max_num = -0x80000000;
  min_num = 0x7fffffff;
  for (i = 0; i < size; i = i + 1) {
    if (max_num < nums[i]) {
      max_num = nums[i];
    }
    if (nums[i] < min_num) {
      min_num = nums[i];
    }
  }
  return max_num + min_num;
}