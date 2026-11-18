char *func0(const char *S) {
  int len = strlen(S);
  if (len == 0) {
    char *empty = malloc(1);
    if (empty) empty[0] = '\0';
    return empty;
  }
  int freq[256] = {0};
  for (int i = 0; i < len; i++) {
    freq[(unsigned char)S[i]]++;
  }
  HeapNode heap[256];
  int heapSize = 0;
  for (int i = 0; i < 256; i++) {
    if (freq[i] > 0) {
      HeapNode node;
      node.freq = freq[i];
      node.ch = (char)i;
      heap[heapSize++] = node;
    }
  }
  for (int i = (heapSize / 2) - 1; i >= 0; i--) {
    heapify_down(heap, heapSize, i);
  }
  if (heapSize > 0 && heap[0].freq * 2 > len + 1) {
    char *empty = malloc(1);
    if (empty) empty[0] = '\0';
    return empty;
  }
  char *result = malloc(len + 1);
  int pos = 0;
  while (heapSize >= 2) {
    HeapNode first = heap_pop(heap, &heapSize);
    HeapNode second = heap_pop(heap, &heapSize);
    result[pos++] = first.ch;
    result[pos++] = second.ch;
    first.freq--;
    second.freq--;
    if (first.freq > 0) {
      heap_push(heap, &heapSize, first);
    }
    if (second.freq > 0) {
      heap_push(heap, &heapSize, second);
    }
  }
  if (heapSize > 0) {
    HeapNode last = heap_pop(heap, &heapSize);
    result[pos++] = last.ch;
  }
  result[pos] = '\0';
  return result;
}