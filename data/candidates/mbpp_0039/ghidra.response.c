char * func0(char *S)

{
  size_t sVar1;
  HeapNode HVar2;
  HeapNode HVar3;
  int iVar4;
  HeapNode last;
  HeapNode second;
  HeapNode first;
  int pos;
  char *result;
  char *empty_1;
  int i_2;
  HeapNode node;
  int i_1;
  int heapSize;
  HeapNode heap [256];
  int i;
  int freq [256];
  char *empty;
  int len;
  char *S_local;
  char *local_10;
  
  sVar1 = strlen(S);
  iVar4 = (int)sVar1;
  if (iVar4 == 0) {
    local_10 = malloc(1);
    if (local_10 != (char *)0x0) {
      *local_10 = '\0';
    }
  }
  else {
    memset(freq,0,0x400);
    for (i = 0; i < iVar4; i = i + 1) {
      freq[(byte)S[i]] = freq[(byte)S[i]] + 1;
    }
    heapSize = 0;
    for (i_1 = 0; i_1 < 0x100; i_1 = i_1 + 1) {
      if (0 < freq[i_1]) {
        node.ch = (char)i_1;
        HVar2.ch = (char)i_1;
        HVar2._5_3_ = node._5_3_;
        HVar2.freq = freq[i_1];
        heap[heapSize] = HVar2;
        heapSize = heapSize + 1;
      }
    }
    i_2 = heapSize / 2;
    while (i_2 = i_2 + -1, -1 < i_2) {
      heapify_down(heap,heapSize,i_2);
    }
    if ((heapSize < 1) || (heap[0].freq * 2 <= iVar4 + 1)) {
      local_10 = malloc((long)(iVar4 + 1));
      pos = 0;
      while (1 < heapSize) {
        HVar2 = heap_pop(heap,&heapSize);
        HVar3 = heap_pop(heap,&heapSize);
        first.ch = HVar2.ch;
        iVar4 = pos + 1;
        local_10[pos] = first.ch;
        second.ch = HVar3.ch;
        pos = pos + 2;
        local_10[iVar4] = second.ch;
        first.freq = HVar2.freq;
        first.freq = first.freq + -1;
        first._4_4_ = HVar2._4_4_;
        second.freq = HVar3.freq;
        second.freq = second.freq + -1;
        second._4_4_ = HVar3._4_4_;
        if (0 < first.freq) {
          heap_push(heap,&heapSize,first);
        }
        if (0 < second.freq) {
          heap_push(heap,&heapSize,second);
        }
      }
      if (0 < heapSize) {
        HVar2 = heap_pop(heap,&heapSize);
        last.ch = HVar2.ch;
        local_10[pos] = last.ch;
        pos = pos + 1;
      }
      local_10[pos] = '\0';
    }
    else {
      local_10 = malloc(1);
      if (local_10 != (char *)0x0) {
        *local_10 = '\0';
      }
    }
  }
  return local_10;
}