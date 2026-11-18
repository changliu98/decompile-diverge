int binary_heap_insert(struct _BinaryHeap *heap, struct _BinaryHeapValue value) {
  if (heap->num_values >= heap->alloced_size) {
    struct _BinaryHeapValue *new_values = ((void *)0);
    unsigned int new_size = heap->alloced_size * 2;
    new_values = xrealloc(heap->values, new_size * sizeof(BinaryHeapValue));
    if (new_values == ((void *)0)) {
      return 0;
    }
    heap->alloced_size = new_size;
    heap->values = new_values;
  }
  unsigned int index = heap->num_values;
  heap->num_values = index + 1;
  while (index > 0 && binary_heap_cmp(heap, heap->values[(index - 1) / 2], value) >= 0) {
    heap->values[index] = heap->values[(index - 1) / 2];
    index = (index - 1) / 2;
  }
  heap->values[index] = value;
  return 1;
}