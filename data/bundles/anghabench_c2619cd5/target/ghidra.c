int binary_search(int *array,int n,int value)

{
  int iVar1;
  int middle;
  int right;
  int left;
  int value_local;
  int n_local;
  int *array_local;
  
  left = 0;
  right = n + -1;
  while( true ) {
    while( true ) {
      if (right < left) {
        return -1;
      }
      iVar1 = left + (right - left >> 1);
      if (array[iVar1] <= value) break;
      right = iVar1 + -1;
    }
    if (value <= array[iVar1]) break;
    left = iVar1 + 1;
  }
  return iVar1;
}