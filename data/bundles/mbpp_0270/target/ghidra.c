int func0(int *arr,int n)

{
  int i;
  int sum;
  int n_local;
  int *arr_local;
  
  sum = 0;
  for (i = 0; i < n; i = i + 2) {
    if (arr[i] % 2 == 0) {
      sum = arr[i] + sum;
    }
  }
  return sum;
}