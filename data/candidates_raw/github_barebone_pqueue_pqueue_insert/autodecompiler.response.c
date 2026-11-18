int heap_push(Heap *heap, long value) {
    size_t index;
    int result;

    if (heap == NULL) {
        result = 1;
        goto end;
    }

    if (heap->length >= heap->capacity) {
        size_t new_capacity;
        long *new_values;

        new_capacity = heap->length + heap->chunk_size;
        new_values = realloc(heap->values, sizeof(long) * new_capacity);
        if (new_values == NULL) {
            result = 1;
            goto end;
        }

        heap->values = new_values;
        heap->capacity = new_capacity;
    }

    index = heap->length++;
    heap->values[index] = value;
    bubble_up(heap, index);

    result = 0;
end:
    return result;
}