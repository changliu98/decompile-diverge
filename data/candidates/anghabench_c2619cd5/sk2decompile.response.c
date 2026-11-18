int binary_search(int *a, int n, int key) {
  int mid, low, high;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = low + ((high - low) >> 1);
    if (a[mid] > key)
      high = mid - 1;
    else if (a[mid] < key)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}