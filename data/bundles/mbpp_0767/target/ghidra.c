int func0(int *arr,int n,int sum)

{
  int j;
  int i;
  int count;
  int sum_local;
  int n_local;
  int *arr_local;
  
  count = 0;
  for (i = 0; j = i, i < n; i = i + 1) {
    while (j = j + 1, j < n) {
      if (arr[i] + arr[j] == sum) {
        count = count + 1;
      }
    }
  }
  return count;
}