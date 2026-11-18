int func0(int *arr,int k)

{
  int i;
  int sum;
  int k_local;
  int *arr_local;
  
  sum = 0;
  for (i = 0; i < k; i = i + 1) {
    if ((-100 < arr[i]) && (arr[i] < 100)) {
      sum = arr[i] + sum;
    }
  }
  return sum;
}