int func0(int* arr, int size) {
  int i;
  for (i = 0; i < size; i++) {
    if (arr[i] % 2 == 0) {
      return arr[i];
    }
  }
  return -1;
}