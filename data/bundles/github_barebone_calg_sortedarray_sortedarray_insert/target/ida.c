int __cdecl sortedarray_insert(SortedArray *sortedarray, SortedArrayValue data)
{
  unsigned int length; // [rsp+4h] [rbp-3Ch]
  SortedArrayValue *data_0; // [rsp+8h] [rbp-38h]
  unsigned int newsize; // [rsp+14h] [rbp-2Ch]
  int order; // [rsp+18h] [rbp-28h]
  unsigned int index; // [rsp+1Ch] [rbp-24h]
  unsigned int right; // [rsp+20h] [rbp-20h]
  unsigned int left; // [rsp+24h] [rbp-1Ch]

  if ( sortedarray )
  {
    left = 0;
    index = 0;
    if ( sortedarray->length <= 1 )
      length = 0;
    else
      length = sortedarray->length;
    right = length;
    while ( left != right )
    {
      index = (right + left) >> 1;
      order = sortedarray->cmp_func(data, sortedarray->data[index]);
      if ( order >= 0 )
      {
        if ( order <= 0 )
          break;
        left = index + 1;
      }
      else
      {
        right = (right + left) >> 1;
      }
    }
    if ( sortedarray->length && sortedarray->cmp_func(data, sortedarray->data[index]) > 0 )
      ++index;
    if ( sortedarray->length + 1 > sortedarray->_alloced )
    {
      newsize = 2 * sortedarray->_alloced;
      data_0 = (SortedArrayValue *)realloc(sortedarray->data, 8LL * newsize);
      if ( !data_0 )
        return 0;
      sortedarray->data = data_0;
      sortedarray->_alloced = newsize;
    }
    memmove(&sortedarray->data[index + 1], &sortedarray->data[index], 8LL * (sortedarray->length - index));
    sortedarray->data[index] = data;
    ++sortedarray->length;
    return 1;
  }
  return 0;
}