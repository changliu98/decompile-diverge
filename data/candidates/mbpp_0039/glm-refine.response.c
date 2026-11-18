char *__cdecl func0(const char *S)
{
    int len = strlen(S);

    // Empty input -> empty heap-allocated string.
    if (len == 0)
    {
        char *empty = (char *)malloc(1);
        if (empty)
            *empty = 0;
        return empty;
    }

    // Frequency histogram over byte values.
    int freq[256];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < len; ++i)
        ++freq[(unsigned char)S[i]];

    // Build a heap of (freq, ch) for every byte that actually occurs.
    HeapNode heap[256];
    int heapSize = 0;
    for (int i = 0; i < 256; ++i)
    {
        if (freq[i] > 0)
        {
            HeapNode node;
            node.freq = freq[i];
            node.ch   = i;
            heap[heapSize++] = node;
        }
    }

    // Heapify the array into a valid heap in O(n).
    for (int i = heapSize / 2 - 1; i >= 0; --i)
        heapify_down(heap, heapSize, i);

    // Feasibility check: the most frequent character must not exceed
    // (len + 1) / 2 occurrences, otherwise two of them must be adjacent.
    if (heapSize > 0 && 2 * heap[0].freq > len + 1)
    {
        char *empty = (char *)malloc(1);
        if (empty)
            *empty = 0;
        return empty;
    }

    // Greedy construction of the result.
    char *result = (char *)malloc(len + 1);
    int pos = 0;

    while (heapSize >= 2)
    {
        HeapNode first  = heap_pop(heap, &heapSize);
        HeapNode second = heap_pop(heap, &heapSize);

        result[pos++] = first.ch;
        result[pos++] = second.ch;

        if (--first.freq > 0)
            heap_push(heap, &heapSize, first);
        if (--second.freq > 0)
            heap_push(heap, &heapSize, second);
    }

    // At most one element can remain; append its single character.
    if (heapSize > 0)
        result[pos++] = heap_pop(heap, &heapSize).ch;

    result[pos] = 0;
    return result;
}