void minmax(int *arr, int *size, int *min, int *max){
  if(*arr>*max) *max = *arr;
  if(*arr<*min) *min = *arr;
}