int func0(int *arr,int arr_size,int x)

{
  int i;
  int count;
  int x_local;
  int arr_size_local;
  int *arr_local;
  
  count = 0;
  for (i = 0; i < arr_size; i = i + 1) {
    if (arr[i] == x) {
      count = count + 1;
    }
  }
  return count;
}