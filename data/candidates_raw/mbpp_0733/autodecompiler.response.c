int binary_search_left(int *arr, int size, int val)
{
 int low = 0, high = size - 1, mid, idx = -1;

 while (low <= high) {
  mid = low + ((high - low) / 2);
  if (val == arr[mid]) {
   idx = mid;
   high = mid - 1;
  } else if (val < arr[mid])
   high = mid - 1;
  else
   low = mid + 1;
 }

 return idx;
}