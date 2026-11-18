int __cdecl binary_heap_insert(BinaryHeap *heap, BinaryHeapValue value)
{
  unsigned int new_size; // [rsp+8h] [rbp-28h]
  unsigned int index; // [rsp+Ch] [rbp-24h]
  BinaryHeapValue *new_values; // [rsp+10h] [rbp-20h]

  if ( heap->num_values >= heap->alloced_size )
  {
    new_size = 2 * heap->alloced_size;
    new_values = (BinaryHeapValue *)realloc(heap->values, 8LL * new_size);
    if ( !new_values )
      return 0;
    heap->alloced_size = new_size;
    heap->values = new_values;
  }
  index = heap->num_values;
  heap->num_values = index + 1;
  while ( index && binary_heap_cmp(heap, heap->values[(index - 1) >> 1], value) >= 0 )
  {
    heap->values[index] = heap->values[(index - 1) >> 1];
    index = (index - 1) >> 1;
  }
  heap->values[index] = value;
  return 1;
}