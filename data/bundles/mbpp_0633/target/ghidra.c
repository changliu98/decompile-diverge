int func0(int *arr,int n)

{
  int j;
  int i;
  int ans;
  int n_local;
  int *arr_local;
  
  ans = 0;
  for (i = 0; j = i, i < n; i = i + 1) {
    while (j = j + 1, j < n) {
      ans = (arr[i] ^ arr[j]) + ans;
    }
  }
  return ans;
}