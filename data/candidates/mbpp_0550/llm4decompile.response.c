int func0(int *arr, int low, int high)
{
 int mid;
 if (low > high)
  return arr[0];
 if (low == high)
  return arr[low];

 mid = low + (high - low) / 2;
 if (mid < high && arr[mid] > arr[mid + 1])
  return arr[mid];
 if (mid > low && arr[mid] < arr[mid - 1])
  return arr[mid - 1];
 if (arr[mid] < arr[low])
  return func0(arr, low, mid - 1);
 return func0(arr, mid + 1, high);
}