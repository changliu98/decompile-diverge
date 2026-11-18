int __cdecl sortedarray_index_of(SortedArray *sortedarray, SortedArrayValue data)
{
  unsigned int length; // [rsp+4h] [rbp-2Ch]
  int order; // [rsp+8h] [rbp-28h]
  unsigned int right; // [rsp+10h] [rbp-20h]
  unsigned int left; // [rsp+14h] [rbp-1Ch]

  if ( !sortedarray )
    return -1;
  left = 0;
  if ( sortedarray->length <= 1 )
    length = 0;
  else
    length = sortedarray->length;
  right = length;
  while ( left != right )
  {
    order = sortedarray->cmp_func(data, sortedarray->data[(right + left) >> 1]);
    if ( order >= 0 )
    {
      if ( order <= 0 )
        return (right + left) >> 1;
      left = ((right + left) >> 1) + 1;
    }
    else
    {
      right = (right + left) >> 1;
    }
  }
  return -1;
}