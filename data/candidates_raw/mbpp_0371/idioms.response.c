int find_min(int *array, int left, int right)
{
  int mid;
  if (left > right)
    return left;
  mid = left + (right - left)/2;
  if (array[mid] == mid)
    return find_min(array, mid+1, right);
  return find_min(array, left, mid-1);
}