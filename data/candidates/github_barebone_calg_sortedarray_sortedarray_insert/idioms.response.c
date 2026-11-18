int sortedarray_insert(struct _sortedarray *array, void *data)
{
  if (array == ((void *)0))
    return 0;
  unsigned int left = 0;
  unsigned int index = 0;
  unsigned int right = (array->length > 1) ? (array->length - 1) : 0;
  while (left != right)
  {
    index = (left + right) / 2;
    int order = array->cmp_func(data, array->data[index]);
    if (order < 0)
      right = index;
    else if (order > 0)
      left = index + 1;
    else
      break;
  }
  if (array->length != 0 && array->cmp_func(data, array->data[index]) > 0)
    ++index;
  if (array->length + 1 > array->_alloced)
  {
    void **newdata = (void **)reallocarray(array->data, (array->_alloced * 2), sizeof(void *));
    if (newdata == ((void *)0))
      return 0;
    array->data = newdata;
    array->_alloced = array->_alloced * 2;
  }
  memmovearray(&array->data[index + 1], &array->data[index], (array->length - index) * sizeof(void *));
  array->data[index] = data;
  ++array->length;
  return 1;
}