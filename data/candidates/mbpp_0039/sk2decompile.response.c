char *func0(char *s) {
  int len = strlen(s);
  if (len == 0) {
    char *ret = malloc(1);
    if (ret) {
      ret[0] = '\0';
    }
    return ret;
  }
  int count[256];
  memset(count, 0, sizeof(count));
  for (int i = 0; i < len; i++) {
    count[(unsigned char)s[i]]++;
  }
  int heap_size = 0;
  struct node heap[256];
  for (int i = 0; i < 256; i++) {
    if (count[i] > 0) {
      struct node n;
      n.freq = count[i];
      n.c = i;
      heap[heap_size++] = n;
    }
  }
  for (int i = heap_size / 2 - 1; i >= 0; i--) {
    heapify_down(heap, heap_size, i);
  }
  if (heap_size > 0 && heap[0].freq * 2 > len + 1) {
    char *ret = malloc(1);
    if (ret) {
      ret[0] = '\0';
    }
    return ret;
  }
  char *ret_str = malloc(len + 1);
  int ret_str_index = 0;
  while (heap_size >= 2) {
    struct node n1 = heap_pop(heap, &heap_size);
    struct node n2 = heap_pop(heap, &heap_size);
    ret_str[ret_str_index++] = n1.c;
    ret_str[ret_str_index++] = n2.c;
    n1.freq--;
    n2.freq--;
    if (n1.freq > 0) {
      heap_push(heap, &heap_size, n1);
    }
    if (n2.freq > 0) {
      heap_push(heap, &heap_size, n2);
    }
  }
  if (heap_size > 0) {
    ret_str[ret_str_index++] = heap_pop(heap, &heap_size).c;
  }
  ret_str[ret_str_index] = '\0';
  return ret_str;
}