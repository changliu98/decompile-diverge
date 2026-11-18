bool sortedarray_insert(SortedArray *sortedarray, SortedArrayValue data)
{
 unsigned int index = 0;
 unsigned int left = 0;
 unsigned int right = sortedarray->length > 1 ? sortedarray->length : 0;
 int order = 0;

 if (!sortedarray)
  return false;

 while (left != right) {
  index = (left + right) / 2;
  order = sortedarray->cmp_func(data, sortedarray->data[index]);
  if (order < 0)
   right = index;
  else if (order > 0)
   left = index + 1;
  else
   break;
 }

 if (sortedarray->length && sortedarray->cmp_func(data, sortedarray->data[index]) > 0)
  index++;

 if (sortedarray->length + 1 > sortedarray->_alloced) {
  unsigned int newsize = sortedarray->_alloced * 2;
  SortedArrayValue *newdata = realloc(sortedarray->data, newsize * sizeof(SortedArrayValue));
  if (!newdata)
   return false;
  sortedarray->data = newdata;
  sortedarray->_alloced = newsize;
 }

 memmove(&sortedarray->data[index + 1], &sortedarray->data[index], (sortedarray->length - index) * sizeof(SortedArrayValue));
 sortedarray->data[index] = data;
 sortedarray->length++;

 return true;
}