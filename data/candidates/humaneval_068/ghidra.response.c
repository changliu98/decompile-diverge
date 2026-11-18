int * func0(int *arr,int length,int *output)

{
  int i;
  int index;
  int smallestEven;
  int *output_local;
  int length_local;
  int *arr_local;
  int *local_10;
  
  smallestEven = 0x7fffffff;
  index = -1;
  for (i = 0; i < length; i = i + 1) {
    if ((arr[i] % 2 == 0) && ((arr[i] < smallestEven || (index == -1)))) {
      smallestEven = arr[i];
      index = i;
    }
  }
  if (index == -1) {
    local_10 = (int *)0x0;
  }
  else {
    *output = smallestEven;
    output[1] = index;
    local_10 = output;
  }
  return local_10;
}