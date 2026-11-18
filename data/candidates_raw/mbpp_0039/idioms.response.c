char *get_min_length_code(char *str)
{
    int i;
    int len;
    int freq[-1];
    int heapSize;
    struct HeapNode heap[-1];
    char *minCode;
    char *minCode1;
    struct HeapNode node;
    struct HeapNode left;
    struct HeapNode right;
    char *minCode2;
    int pos;
    char *minCode3;
    char *minCode4;
    int j;
    len = strlen(str);
    if (len == 0)
    {
        minCode = (char *)malloc(sizeof(char));
        if (minCode != ((void *)0))
        {
            minCode[0] = '\0';
        }
        return minCode;
    }
    memset(freq, 0, sizeof(int) * 256);
    for (i = 0; i < len; i++)
    {
        freq[(int)str[i]] += 1;
    }
    heapSize = 0;
    for (i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            node.freq = freq[i];
            node.ch = (char) i;
            heap[heapSize++] = node;
        }
    }
    for (i = (heapSize / 2) - 1; i >= 0; i--)
    {
        heapify_down(heap, heapSize, i);
    }
    if (heapSize > 0 && (heap[0].freq * 2) > (len + 1))
    {
        minCode = (char *)malloc(sizeof(char));
        if (minCode != ((void *)0))
        {
            minCode[0] = '\0';
        }
        return minCode;
    }
    minCode = (char *)malloc((len + 1) * sizeof(char));
    pos = 0;
    while (heapSize >= 2)
    {
        left = heap_pop(heap, &heapSize);
        right = heap_pop(heap, &heapSize);
        minCode[pos++] = left.ch;
        minCode[pos++] = right.ch;
        left.freq -= 1;
        right.freq -= 1;
        if (left.freq > 0)
        {
            heap_push(heap, &heapSize, left);
        }
        if (right.freq > 0)
        {
            heap_push(heap, &heapSize, right);
        }
    }
    if (heapSize > 0)
    {
        minCode[pos++] = heap_pop(heap, &heapSize).ch;
    }
    minCode[pos] = '\0';
    return minCode;
}