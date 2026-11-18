int func0(int *nums,int size)

{
  int i;
  int size_local;
  int *nums_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return -1;
    }
    if (nums[i] % 2 == 0) break;
    i = i + 1;
  }
  return nums[i];
}