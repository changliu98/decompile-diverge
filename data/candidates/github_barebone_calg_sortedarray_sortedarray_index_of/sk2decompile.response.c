int sortedarray_index_of(SortedArray *array, SortedArrayValue value) {
  unsigned int min, max, mid;
  int cmp;
  if (array == NULL) return -1;
  min = 0;
  max = (array->length > 1) ? array->length : 0;
  while (min != max) {
    mid = (min + max) / 2;
    cmp = array->compare(value, array->values[mid]);
    if (cmp < 0)
      max = mid;
    else if (cmp > 0)
      min = mid + 1;
    else
      return mid;
  }
  return -1;
}