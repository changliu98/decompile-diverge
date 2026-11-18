_Bool func0(int *arr,int n)

{
  int i;
  int n_local;
  int *arr_local;
  
  i = 0;
  while( true ) {
    if (n <= i) {
      return false;
    }
    if ((arr[i] & 1U) == 0) break;
    i = i + 1;
  }
  return true;
}