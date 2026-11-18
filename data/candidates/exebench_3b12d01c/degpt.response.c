int int2arr(int *arr,int num)

{
  int i;
  int num_local;
  int *arr_local;
  
  i = 0;
  for (num_local = num; num_local != 0; num_local = num_local / 10) {
    arr[i] = num_local % 10;
    i = i + 1;
  }
  return i;
}