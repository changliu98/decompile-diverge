void func0(int *nums,int size,int *result)

{
  int i;
  int *result_local;
  int size_local;
  int *nums_local;
  
  for (i = 0; i < size + -1; i = i + 1) {
    result[i] = nums[i] + nums[i + 1];
  }
  return;
}