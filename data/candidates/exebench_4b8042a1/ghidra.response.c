int next_arr_seq(int *arr,int len,int maxval)

{
  int i;
  int maxval_local;
  int len_local;
  int *arr_local;
  
  i = 0;
  while( true ) {
    if (len <= i) {
      return 0;
    }
    arr[i] = arr[i] + 1;
    if (arr[i] <= maxval) break;
    arr[i] = 0;
    i = i + 1;
  }
  return 1;
}