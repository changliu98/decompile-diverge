int __cdecl binary_heap_insert(BinaryHeap *heap, BinaryHeapValue value)
{
  unsigned int new_size; 
  unsigned int index; 
  BinaryHeapValue *new_values; 

  // Double the allocated size if the heap is currently full
  if (heap->num_values >= heap->alloced_size)
  {
    new_size = heap->alloced_size * 2;
    new_values = (BinaryHeapValue *)realloc(heap->values, sizeof(BinaryHeapValue) * new_size);
    if (!new_values)
      return 0;
    
    heap->alloced_size = new_size;
    heap->values = new_values;
  }

  // Add the new value at the end and bubble it up
  index = heap->num_values;
  heap->num_values = index + 1;

  // While not at the root, if the parent node is greater than or equal to the new value
  while (index > 0 && binary_heap_cmp(heap, heap->values[(index - 1) / 2], value) >= 0)
  {
    // Move the parent down to the child's position
    heap->values[index] = heap->values[(index - 1) / 2];
    
    // Move up to the parent's index
    index = (index - 1) / 2;
  }

  // Place the new value in its correct sorted position
  heap->values[index] = value;
  
  return 1;
}