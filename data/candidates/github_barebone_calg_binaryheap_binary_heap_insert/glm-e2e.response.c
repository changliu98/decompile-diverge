int binary_heap_insert(binary_heap *heap, void *item) {
    if (heap->num_entries >= heap->capacity) {
        int new_capacity = heap->capacity * 2;
        void **new_elems = realloc(heap->elems, new_capacity * sizeof(void *));
        if (!new_elems) {
            return 0;
        }
        heap->capacity = new_capacity;
        heap->elems = new_elems;
    }

    int index = heap->num_entries;
    heap->num_entries++;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->cmp(heap, heap->elems[parent]) < 0) {
            break;
        }
        heap->elems[index] = heap->elems[parent];
        index = parent;
    }

    heap->elems[index] = item;
    return 1;
}