void minmax(int *arr,int size,int *min,int *max)

{
  int *max_local;
  int *min_local;
  int size_local;
  int *arr_local;
  
  if (*arr < *min) {
    *min = *arr;
  }
  if (*max < *arr) {
    *max = *arr;
  }
  return;
}