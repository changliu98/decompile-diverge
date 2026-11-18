// This function implements a modified binary search to find a local minimum 
// in an array. It assumes the array elements are distinct (or at least strictly 
// decreasing/increasing at the boundaries) based on the comparison logic.
// It returns the value of a local minimum element.
int __cdecl find_local_minimum(int *arr, int low, int high)
{
  int mid; // [rsp+4h] [rbp-1Ch]

  // Base case 1: Invalid range. 
  // Note: If high < low, it returns the element at the base pointer of the array (*arr).
  if (high < low)
    return *arr;

  // Base case 2: Single element left. A single element is trivially a local minimum.
  if (high == low)
    return arr[low];

  // Calculate the middle index safely to avoid integer overflow.
  mid = low + (high - low) / 2;

  // Check if the element immediately to the right of 'mid' is smaller.
  // If so, 'mid' is a local minimum (assuming distinct elements).
  if (mid < high && arr[mid + 1] < arr[mid])
    return arr[mid];

  // Check if the element immediately to the left of 'mid' is smaller.
  // If so, 'mid - 1' is a local minimum.
  if (mid > low && arr[mid] < arr[mid - 1])
    return arr[mid - 1];

  // If the left half is sorted in non-decreasing order, then the dip 
  // (local minimum) must be in the right half.
  if (arr[low] <= arr[mid])
    return find_local_minimum(arr, mid + 1, high);

  // Otherwise, the dip must be in the left half.
  return find_local_minimum(arr, low, mid - 1);
}