int func0(int *arr,int n)

{
  int i_1;
  int left_sum;
  int i;
  int total_sum;
  int n_local;
  int *arr_local;
  
  total_sum = 0;
  for (i = 0; i < n; i = i + 1) {
    total_sum = arr[i] + total_sum;
  }
  left_sum = 0;
  i_1 = 0;
  while( true ) {
    if (n <= i_1) {
      return -1;
    }
    total_sum = total_sum - arr[i_1];
    if (left_sum == total_sum) break;
    left_sum = arr[i_1] + left_sum;
    i_1 = i_1 + 1;
  }
  return i_1;
}