bool _isSorted(int *arr, int size) {
  bool asc = true;
  bool desc = true;
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) asc = false;
    if (arr[i] < arr[i + 1]) desc = false;
  }
  return asc || desc;
}