int func0(int *arr,int size)

{
  int i;
  int max;
  int size_local;
  int *arr_local;
  
  max = -1;
  for (i = 1; i < size; i = i + 1) {
    if (arr[i] < arr[i + -1]) {
      max = i;
    }
  }
  return max;
}