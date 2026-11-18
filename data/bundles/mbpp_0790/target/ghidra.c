_Bool func0(int *nums,int length)

{
  int i;
  int length_local;
  int *nums_local;
  
  i = 0;
  while( true ) {
    if (length <= i) {
      return true;
    }
    if (nums[i] % 2 != i % 2) break;
    i = i + 1;
  }
  return false;
}