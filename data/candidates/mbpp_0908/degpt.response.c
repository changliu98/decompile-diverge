int func0(int *arr,int n)

{
  int i;
  int n_local;
  int *arr_local;
  
  i = 0;
  while( true ) {
    if (n <= i) {
      return -1;
    }
    if (arr[i] == i) break;
    i = i + 1;
  }
  return i;
}