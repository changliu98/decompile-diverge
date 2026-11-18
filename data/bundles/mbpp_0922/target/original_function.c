void func0(int arr[], int arr_len, int *x, int *y) {
  if (arr_len < 2) {
    *x = 0;
    *y = 0;
    return;
  }
  *x = arr[0];
  *y = arr[1];
  for (int i = 0; i < arr_len; i++) {
    for (int j = i + 1; j < arr_len; j++) {
      if (arr[i] * arr[j] > (*x) * (*y)) {
        *x = arr[i];
        *y = arr[j];
      }
    }
  }
}