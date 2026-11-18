int num_to_array(int *arr,int num)

{
  int i;
  int digit;
  int num_local;
  int *arr_local;
  
  i = 0;
  for (num_local = num; 0 < num_local; num_local = num_local / 10) {
    arr[i] = num_local % 10;
    i = i + 1;
  }
  return i;
}