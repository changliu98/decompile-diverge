int func0(int *arr, int size, int target) {
  int low = 0;
  int high = size - 1;
  int mid;
  int found = -1;

  while (low <= high) {

    mid = (low + high) / 2;
    if (target == arr[mid]) {
      found = mid;
      low = mid + 1;
    } else if (target < arr[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return found;
}