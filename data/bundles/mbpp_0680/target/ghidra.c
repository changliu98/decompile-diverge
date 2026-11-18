_Bool func0(int *nums,int size)

{
  int i;
  int size_local;
  int *nums_local;
  
  i = 0;
  while( true ) {
    if (size + -1 <= i) {
      return true;
    }
    if (nums[i + 1] < nums[i]) break;
    i = i + 1;
  }
  return false;
}