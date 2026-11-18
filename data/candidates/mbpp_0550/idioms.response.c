int func0(int *array, int low, int high)
{
  int mid;
  if (high < low)
    return array[0];
  if (high == low)
    return array[low];
  mid = low + (high - low)/2;
  if (mid < high && array[mid + 1] < array[mid])
    return array[mid];
  if (mid > low && array[mid] < array[mid - 1])
    return array[mid - 1];
  if (array[low] <= array[mid])
    return func0(array, mid + 1, high);
  return func0(array, low, mid - 1);
}