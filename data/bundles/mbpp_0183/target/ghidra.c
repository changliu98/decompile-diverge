int func0(int *arr,int n,int k)

{
  int j;
  int i;
  int count;
  int k_local;
  int n_local;
  int *arr_local;
  
  count = 0;
  for (i = 0; j = i, i < n; i = i + 1) {
    while (j = j + 1, j < n) {
      if ((arr[i] - arr[j] == k) || (arr[j] - arr[i] == k)) {
        count = count + 1;
      }
    }
  }
  return count;
}