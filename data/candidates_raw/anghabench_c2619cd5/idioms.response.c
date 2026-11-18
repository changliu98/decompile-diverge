int bsearch(int *array, int n, int value)
{
  int left = 0;
  int right = n - 1;
  int middle;
  while (left <= right) {
    middle = left + (right - left)/2;
    if (array[middle] > value)
      right = middle - 1;
    else if (array[middle] < value)
      left = middle + 1;
    else
      return middle;
  }
  return -1;
}