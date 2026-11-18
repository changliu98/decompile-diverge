int func0(int *arr, int size) {
  sortArray(arr, size);
  int i, count = 0, max = 0, min = size;
  for (i = 0; i < size - 1; i++) {
    if (arr[i] == arr[i + 1]) {
      count++;
    } else {
      max = max > count ? max : count;
      min = min < count ? min : count;
      count = 0;
    }
  }
  return max - min;
}