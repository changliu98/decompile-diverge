int func0(int *array, int x, int n)
{
  int low = 0;
  int high = n-1;
  int mid;
  int result = -1;
  while (low <= high)
  {
    mid = (low + high)/2;
    if (array[mid] > x)
    {
      high = mid - 1;
    }
    else if (array[mid] < x)
    {
      low = mid + 1;
    }
    else
    {
      result = mid;
    }
  }
  return (result);
}