int min(int *array, int n)
{
  int left = 0;
  int right = n - 1;
  int mid;
  while (left <= right) {
    if (array[left] <= array[right])
      return left;
    mid = (right + left) / 2;
    if (array[mid] <= array[(mid + 1) % n] && array[mid] <= array[(mid + (right + left) / 2 - 1 + n) % n])
      return (right + left) / 2;
    if (array[mid] > array[right])
      right = mid - 1;
    else if (array[mid] < array[left])
      left = mid + 1;
  }
  return -1;
}