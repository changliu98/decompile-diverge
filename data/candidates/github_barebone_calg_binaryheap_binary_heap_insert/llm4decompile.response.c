int binary_heap_insert(BinaryHeap *heap, BinaryHeapValue value)
{
    unsigned int index;
    unsigned int parent;
    unsigned int new_size;
    BinaryHeapValue *new_values;





    if (heap->num_values >= heap->alloced_size) {
        new_size = heap->alloced_size * 2;
        new_values = realloc(heap->values, new_size * sizeof(BinaryHeapValue));
        if (new_values == NULL) {
            return 0;
        }
        heap->alloced_size = new_size;
        heap->values = new_values;
    }





    index = heap->num_values;
    ++heap->num_values;





    while (index > 0) {
        parent = (index - 1) / 2;
        if (binary_heap_cmp(heap, heap->values[parent], value) < 0) {
            break;
        }
        heap->values[index] = heap->values[parent];
        index = parent;
    }





    heap->values[index] = value;

    return 1;
}