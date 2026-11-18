int set1d(double *arr,double value)

{
  int i;
  double value_local;
  double *arr_local;
  
  for (i = 0; i < 0x28; i = i + 1) {
    arr[i] = value;
  }
  return 0;
}