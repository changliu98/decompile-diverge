char *func0(const char *str) {
    int len = strlen(str);
    if (len == 0) {
        char *result = malloc(1);
        if (result)
            result[0] = '\0';
        return result;
    }

    int count[256];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }

    HeapNode heap[256];
    int heap_size = 0;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0) {
            heap[heap_size].freq = count[i];
            heap[heap_size].ch = (unsigned char)i;
            heap_size++;
        }
    }

    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        heapify_down(heap, heap_size, i);
    }

    if (heap_size > 0 && heap[0].freq * 2 > len + 1) {
        char *result = malloc(1);
        if (result)
            result[0] = '\0';
        return result;
    }

    char *result = malloc(len + 1);
    int idx = 0;

    while (heap_size >= 2) {
        HeapNode n1 = heap_pop(heap, &heap_size);
        HeapNode n2 = heap_pop(heap, &heap_size);
        result[idx++] = n1.ch;
        result[idx++] = n2.ch;
        n1.freq--;
        n2.freq--;
        if (n1.freq > 0)
            heap_push(heap, &heap_size, n1);
        if (n2.freq > 0)
            heap_push(heap, &heap_size, n2);
    }

    if (heap_size > 0) {
        HeapNode n = heap_pop(heap, &heap_size);
        result[idx++] = n.ch;
    }

    result[idx] = '\0';
    return result;
}