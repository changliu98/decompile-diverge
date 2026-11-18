int sortedarray_search(struct _SortedArray *sortedarray, void *data)
{
  int left;
  int right;
  int order;
  if (sortedarray == ((void *)0))
    return -1;
  left = 0;
  if (sortedarray->length > 1)
    right = sortedarray->length - 1;
  else
    right = 0;
  while (left != right)
  {
    int mid = (left + right) >> 1;
    order = sortedarray->cmp_func(data, sortedarray->data[mid]);
    if (order < 0)
      right = mid;
    else if (order > 0)
      left = mid + 1;
    else
      return mid;
  }
  return -1;
}