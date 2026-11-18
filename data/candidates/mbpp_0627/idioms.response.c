int func0(int *array, int start, int end)
{
  int mid;
  if (start > end)
    return end + 1;
  if (array[start] != start)
    return start;
  mid = (start + end) / 2;
  if (array[mid] == mid)
    return func0(array, mid + 1, end);
  return func0(array, start, mid);
}