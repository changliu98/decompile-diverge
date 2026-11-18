int sortedarray_index_of(SortedArray *sortedarray, SortedArrayValue data)
{
 unsigned int left, right, mid;
 int cmp_result;

 if (sortedarray == NULL)
  return -1;

 left = 0;
 right = sortedarray->length > 1 ? sortedarray->length : 0;

 while (left != right) {
  mid = (left + right) / 2;
  cmp_result = sortedarray->cmp_func(data, sortedarray->data[mid]);
  if (cmp_result < 0)
   right = mid;
  else if (cmp_result > 0)
   left = mid + 1;
  else
   return mid;
 }

 return -1;
}