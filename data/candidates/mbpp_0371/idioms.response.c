int func0(int *array, int left, int right)
{
  int mid;
  if (left > right)
    return left;
  mid = left + (right - left)/2;
  if (array[mid] == mid)
    return func0(array, mid+1, right);
  return func0(array, left, mid-1);
}