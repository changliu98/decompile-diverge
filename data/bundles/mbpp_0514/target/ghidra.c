int func0(int *arr,int len)

{
  int i;
  int sum;
  int len_local;
  int *arr_local;
  
  sum = 0;
  for (i = 0; i < len; i = i + 1) {
    sum = arr[i] + sum;
  }
  return sum;
}