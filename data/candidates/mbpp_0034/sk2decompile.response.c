int _find_missing(int *arr, int n) {
  int mid, low, high;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (high + low) / 2;
    if (arr[mid] != mid + 1 && arr[mid - 1] == mid) return mid + 1;
    if (arr[mid] == mid + 1)
      low = mid + 1;
    else
      high = mid - 1;
  }
  return -1;
}