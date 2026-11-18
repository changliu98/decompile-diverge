int func0(int *arr,int n)

{
  int local_2c;
  int local_28;
  int i;
  int min_count;
  int max_count;
  int count;
  int n_local;
  int *arr_local;
  
  sortArray(arr,n);
  count = 0;
  max_count = 0;
  min_count = n;
  for (i = 0; i < n + -1; i = i + 1) {
    if (arr[i] == arr[i + 1]) {
      count = count + 1;
    }
    else {
      if (count < max_count) {
        local_28 = max_count;
      }
      else {
        local_28 = count;
      }
      max_count = local_28;
      if (min_count < count) {
        local_2c = min_count;
      }
      else {
        local_2c = count;
      }
      min_count = local_2c;
      count = 0;
    }
  }
  return max_count - min_count;
}