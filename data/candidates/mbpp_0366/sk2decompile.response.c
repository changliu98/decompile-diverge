int func0(int* arr, int size) {
  int max = arr[0] * arr[1];
  for (int i = 1; i < size - 1; i++) {
    if (arr[i] * arr[i + 1] > max) {
      max = arr[i] * arr[i + 1];
    }
  }
  return max;
}