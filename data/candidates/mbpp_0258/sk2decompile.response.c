int func0(int* arr, int size) {
  int i, count = 0;
  for (i = 0; i < size; i++) {
    if (arr[i] % 2) {
      count++;
    }
  }
  return count;
}