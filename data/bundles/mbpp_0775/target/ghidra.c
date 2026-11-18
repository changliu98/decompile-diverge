_Bool func0(int *nums,int size)

{
  int i;
  int size_local;
  int *nums_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return true;
    }
    if (nums[i] % 2 != i % 2) break;
    i = i + 1;
  }
  return false;
}