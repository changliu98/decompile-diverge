int func0(int *arr,int n,int k)

{
  int i_1;
  int i;
  int res;
  int max1;
  int k_local;
  int n_local;
  int *arr_local;
  
  max1 = *arr;
  res = 0;
  for (i = 1; i < n; i = i + 1) {
    if (max1 < arr[i]) {
      max1 = arr[i];
    }
  }
  i_1 = 0;
  while( true ) {
    if (n <= i_1) {
      return res;
    }
    if ((max1 - arr[i_1]) % k != 0) break;
    res = (max1 - arr[i_1]) / k + res;
    i_1 = i_1 + 1;
  }
  return -1;
}