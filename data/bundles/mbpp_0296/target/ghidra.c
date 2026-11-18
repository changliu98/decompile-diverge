int func0(int *arr,int n)

{
  int j;
  int i;
  int inv_count;
  int n_local;
  int *arr_local;
  
  inv_count = 0;
  for (i = 0; j = i, i < n; i = i + 1) {
    while (j = j + 1, j < n) {
      if (arr[j] < arr[i]) {
        inv_count = inv_count + 1;
      }
    }
  }
  return inv_count;
}