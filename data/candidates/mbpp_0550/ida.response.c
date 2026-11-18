int __cdecl func0(int *arr, int low, int high)
{
  int mid; // [rsp+4h] [rbp-1Ch]

  if ( high < low )
    return *arr;
  if ( high == low )
    return arr[low];
  mid = (high - low) / 2 + low;
  if ( mid < high && arr[mid + 1] < arr[mid] )
    return arr[mid];
  if ( mid > low && arr[mid] < arr[mid - 1] )
    return arr[mid - 1];
  if ( arr[low] <= arr[mid] )
    return func0(arr, mid + 1, high);
  return func0(arr, low, mid - 1);
}