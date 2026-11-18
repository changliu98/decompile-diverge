char* func0(char* S)
{
    int freq[256];
    HeapNode heap[256];
    int heapSize;
    int S_len;
    char* result;
    int i;
    int pos;

    S_len = strlen(S);
    if (S_len == 0)
    {
        result = (char*)malloc(1);
        if (result != NULL)
            *result = '\0';
        return result;
    }

    memset(freq, 0, sizeof(freq));
    for (i = 0; i < S_len; i++)
        freq[S[i]]++;

    heapSize = 0;
    for (i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            HeapNode node;
            node.ch = i;
            node.freq = freq[i];
            heap[heapSize] = node;
            heapSize++;
        }
    }

    for (i = heapSize / 2 - 1; i >= 0; i--)
        heapify_down(heap, heapSize, i);

    if (heapSize > 0 && heap[0].freq * 2 > S_len + 1)
    {
        result = (char*)malloc(1);
        if (result != NULL)
            *result = '\0';
        return result;
    }

    result = (char*)malloc(S_len + 1);
    pos = 0;
    while (heapSize > 1)
    {
        HeapNode first;
        HeapNode second;
        first = heap_pop(heap, &heapSize);
        second = heap_pop(heap, &heapSize);
        result[pos++] = first.ch;
        result[pos++] = second.ch;
        first.freq--;
        second.freq--;
        if (first.freq > 0)
            heap_push(heap, &heapSize, first);
        if (second.freq > 0)
            heap_push(heap, &heapSize, second);
    }
    if (heapSize > 0)
    {
        HeapNode last;
        last = heap_pop(heap, &heapSize);
        result[pos++] = last.ch;
    }
    result[pos] = '\0';

    return result;
}