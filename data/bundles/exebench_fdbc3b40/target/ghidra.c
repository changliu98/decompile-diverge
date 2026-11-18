void multiply_all(int *arr,int num)

{
  int i;
  int num_local;
  int *arr_local;
  
  for (i = 0; i < 10; i = i + 1) {
    arr[i] = num * arr[i];
  }
  return;
}