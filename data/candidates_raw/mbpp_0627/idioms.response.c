int find_min(int *array, int start, int end)
{
  int mid;
  if (start > end)
    return end + 1;
  if (array[start] != start)
    return start;
  mid = (start + end) / 2;
  if (array[mid] == mid)
    return find_min(array, mid + 1, end);
  return find_min(array, start, mid);
}