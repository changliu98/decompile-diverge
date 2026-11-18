int func0(int *arr,int n)

{
  int i;
  int n_local;
  int *arr_local;
  
  i = 1;
  while( true ) {
    if (n <= i) {
      return 0;
    }
    if (arr[i] < arr[i + -1]) break;
    i = i + 1;
  }
  return i;
}