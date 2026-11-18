void func0(int *arr,int n,int *result)

{
  int i;
  int *result_local;
  int n_local;
  int *arr_local;
  
  qsort(arr,(long)n,4,cmpfunc);
  for (i = 0; i < n; i = i + 1) {
    result[i] = arr[i];
  }
  return;
}