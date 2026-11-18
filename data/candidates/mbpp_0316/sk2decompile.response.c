int _binary_search_right(int *a, int n, int key) {
  int left = 0;
  int right = n - 1;
  int result = -1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (a[mid] == key) {
      result = mid;
      left = mid + 1;
    } else if (a[mid] < key) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}