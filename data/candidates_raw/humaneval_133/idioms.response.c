int sum_ceil(float *array, int size){
  int sum = 0;
  int i = 0;
  for (i = 0; i < size; i++){
    int ceil_int = (int) ceil(array[i]);
    sum += ceil_int * ceil_int;
  }
  return sum;
}