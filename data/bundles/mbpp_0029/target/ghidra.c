int func0(int *arr,int arr_size)

{
  int j;
  int count;
  int i;
  int arr_size_local;
  int *arr_local;
  
  i = 0;
  while( true ) {
    if (arr_size <= i) {
      return -1;
    }
    count = 0;
    for (j = 0; j < arr_size; j = j + 1) {
      if (arr[i] == arr[j]) {
        count = count + 1;
      }
    }
    if (count % 2 != 0) break;
    i = i + 1;
  }
  return arr[i];
}