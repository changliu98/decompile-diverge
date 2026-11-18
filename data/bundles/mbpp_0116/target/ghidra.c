int func0(int *nums,int size)

{
  int i;
  int result;
  int size_local;
  int *nums_local;
  
  result = 0;
  for (i = 0; i < size; i = i + 1) {
    result = result * 10 + nums[i];
  }
  return result;
}