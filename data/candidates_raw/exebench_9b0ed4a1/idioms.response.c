float bsearch(float value, float *array, int size)
{
  int low; int high; int mid;
  if (array[0] == value)
    return 0.0;
  if (array[0] > value)
    return -1.0;
  if (array[size - 1] < value)
    return -1.0;
  if (array[size - 1] == value)
    return (size - 1);
  low = 0;
  high = size - 1;
  while (low <= high)
  {
    mid = (low + high) / 2;
    if (array[mid] > value)
      high = mid - 1;
    else if (array[mid] < value)
      low = mid + 1;
    else
      return (float)mid;
  }
  float f = (value - array[high]) / (array[low] - array[high]);
  return (float)(high * (1 - f) + low * f);
}