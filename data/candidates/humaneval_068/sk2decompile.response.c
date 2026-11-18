int* func0(int* arr, int arr_size, int* result) {
  int min = 2147483647;
  int index = -1;
  for (int i = 0; i < arr_size; i++) {
    if (arr[i] % 2 == 0) {
      if (arr[i] < min || index == -1) {
        min = arr[i];
        index = i;
      }
    }
  }
  if (index == -1) {
    return NULL;
  }
  result[0] = min;
  result[1] = index;
  return result;
}