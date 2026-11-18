int func0(int *arr,int n)

{
  int j;
  int i;
  int cnt;
  int n_local;
  int *arr_local;
  
  cnt = 0;
  for (i = 0; j = i, i < n; i = i + 1) {
    while (j = j + 1, j < n) {
      if (arr[i] != arr[j]) {
        cnt = cnt + 1;
      }
    }
  }
  return cnt;
}