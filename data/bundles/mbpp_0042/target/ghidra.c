int func0(int *arr,int n)

{
  int j;
  int count;
  int i;
  int sum;
  int n_local;
  int *arr_local;
  
  sum = 0;
  for (i = 0; i < n; i = i + 1) {
    count = 1;
    for (j = 0; j < n; j = j + 1) {
      if ((arr[j] == arr[i]) && (j != i)) {
        count = count + 1;
      }
    }
    if (1 < count) {
      sum = arr[i] + sum;
    }
  }
  return sum;
}