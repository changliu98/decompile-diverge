int func0(int *nums,int size)

{
  int i;
  int product;
  int size_local;
  int *nums_local;
  
  product = 1;
  for (i = 0; i < size; i = i + 1) {
    product = nums[i] * product;
  }
  return product;
}