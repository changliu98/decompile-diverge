int max(float *arr)

{
  float highest;
  int ret;
  int i;
  float *arr_local;
  
  ret = 0;
  highest = *arr;
  for (i = 0; (uint)i < 2; i = i + 1) {
    if (highest < arr[i]) {
      ret = i;
      highest = arr[i];
    }
  }
  return ret;
}