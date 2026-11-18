int func0(int *array, int n, int x)
{
  int left = 0;
  int right = n - 1;
  int mid;
  int result = -1;
  while (left <= right)
  {
    mid = (left + right) / 2;
    if (array[mid] == x)
    {
      result = mid;
      left = mid + 1;
    }
    else if (array[mid] > x)
    {
      right = mid - 1;
    }
    else
    {
      left = mid + 1;
    }
  }
  return result;
}