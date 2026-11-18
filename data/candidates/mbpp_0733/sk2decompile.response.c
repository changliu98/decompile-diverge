int _binary_search_last_equal(int *array, int len, int value) {
  int low = 0;
  int high = len - 1;
  int result = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (array[mid] == value) {
      result = mid;
      high = mid - 1;
    } else if (array[mid] < value) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return result;
}