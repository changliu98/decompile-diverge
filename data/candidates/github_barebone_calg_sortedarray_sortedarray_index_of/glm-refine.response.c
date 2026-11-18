int __cdecl sortedarray_index_of(SortedArray *sortedarray, SortedArrayValue data)
{
  unsigned int left, right, mid, length;
  int order;

  if (!sortedarray)
    return -1;

  // Determine the search space. 
  // If length is 1 or less, length is set to 0, making the search space empty.
  length = (sortedarray->length <= 1) ? 0 : sortedarray->length;
  
  left = 0;
  right = length;

  // Standard binary search
  while (left != right)
  {
    mid = (right + left) / 2;
    order = sortedarray->cmp_func(data, sortedarray->data[mid]);

    if (order == 0)
    {
      return mid;       // Element found
    }
    else if (order > 0)
    {
      left = mid + 1;   // Search in the right half
    }
    else
    {
      right = mid;      // Search in the left half
    }
  }

  return -1;            // Element not found
}