void func0(int *arr,int arr_len,int *x,int *y)

{
  int j;
  int i;
  int *y_local;
  int *x_local;
  int arr_len_local;
  int *arr_local;
  
  if (arr_len < 2) {
    *x = 0;
    *y = 0;
  }
  else {
    *x = *arr;
    *y = arr[1];
    for (i = 0; j = i, i < arr_len; i = i + 1) {
      while (j = j + 1, j < arr_len) {
        if (*x * *y < arr[i] * arr[j]) {
          *x = arr[i];
          *y = arr[j];
        }
      }
    }
  }
  return;
}