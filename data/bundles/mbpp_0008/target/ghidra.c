void func0(int *nums,int *result,int size)

{
  int i;
  int size_local;
  int *result_local;
  int *nums_local;
  
  for (i = 0; i < size; i = i + 1) {
    result[i] = nums[i] * nums[i];
  }
  return;
}