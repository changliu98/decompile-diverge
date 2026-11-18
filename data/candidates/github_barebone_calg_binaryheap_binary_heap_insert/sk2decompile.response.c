int binary_heap_insert(binary_heap_t *binary_heap, binary_heap_data_t data) {
  if (binary_heap->size >= binary_heap->capacity) {
    unsigned int new_capacity = binary_heap->capacity * 2;
    binary_heap_data_t *new_data = realloc(
        binary_heap->data, new_capacity * sizeof(binary_heap_data_t));
    if (new_data == NULL) return 0;
    binary_heap->capacity = new_capacity;
    binary_heap->data = new_data;
  }
  unsigned int i = binary_heap->size;
  binary_heap->size++;
  while (i > 0) {
    unsigned int parent = (i - 1) / 2;
    if (binary_heap_cmp(binary_heap, binary_heap->data[parent], data) < 0)
      break;
    binary_heap->data[i] = binary_heap->data[parent];
    i = parent;
  }
  binary_heap->data[i] = data;
  return 1;
}