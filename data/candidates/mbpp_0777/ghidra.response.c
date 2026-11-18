int func0(int *arr,int n)

{
  int i;
  int sum;
  int n_local;
  int *arr_local;
  
  qsort(arr,(long)n,4,compare);
  sum = *arr;
  for (i = 0; i < n + -1; i = i + 1) {
    if (arr[i] != arr[i + 1]) {
      sum = arr[i + 1] + sum;
    }
  }
  return sum;
}