// local variable allocation has failed, the output may be wrong!
char *__cdecl func0(const char *S)
{
  int v1; // eax
  HeapNode v2; // rax
  int v3; // ecx
  HeapNode v4; // rdx OVERLAPPED
  HeapNode v5; // rdx OVERLAPPED
  char ch; // dl
  int v7; // ecx
  HeapNode second; // [rsp+10h] [rbp-C70h]
  HeapNode first; // [rsp+18h] [rbp-C68h]
  int pos; // [rsp+24h] [rbp-C5Ch]
  char *result; // [rsp+28h] [rbp-C58h]
  char *empty_0; // [rsp+30h] [rbp-C50h]
  int i_1; // [rsp+3Ch] [rbp-C44h]
  HeapNode node; // [rsp+40h] [rbp-C40h]
  int i_0; // [rsp+48h] [rbp-C38h]
  int heapSize; // [rsp+4Ch] [rbp-C34h] BYREF
  HeapNode heap[256]; // [rsp+50h] [rbp-C30h] BYREF
  int i; // [rsp+85Ch] [rbp-424h]
  int freq[256]; // [rsp+860h] [rbp-420h] BYREF
  char *empty; // [rsp+C60h] [rbp-20h]
  int len; // [rsp+C6Ch] [rbp-14h]
  const char *Sa; // [rsp+C70h] [rbp-10h]

  Sa = S;
  len = strlen(S);
  if ( len )
  {
    memset(freq, 0, sizeof(freq));
    for ( i = 0; i < len; ++i )
      ++freq[(unsigned __int8)Sa[i]];
    heapSize = 0;
    for ( i_0 = 0; i_0 < 256; ++i_0 )
    {
      if ( freq[i_0] > 0 )
      {
        node.freq = freq[i_0];
        node.ch = i_0;
        v1 = heapSize++;
        heap[v1] = node;
      }
    }
    for ( i_1 = heapSize / 2 - 1; i_1 >= 0; --i_1 )
      heapify_down(heap, heapSize, i_1);
    if ( heapSize <= 0 || 2 * heap[0].freq <= len + 1 )
    {
      result = (char *)malloc(len + 1);
      pos = 0;
      while ( heapSize >= 2 )
      {
        first = heap_pop(heap, &heapSize);
        v2 = heap_pop(heap, &heapSize);
        *(_DWORD *)&second.ch = *(_DWORD *)&v2.ch;
        result[pos] = first.ch;
        v3 = pos + 1;
        pos += 2;
        result[v3] = v2.ch;
        --first.freq;
        second.freq = v2.freq - 1;
        if ( first.freq > 0 )
        {
          v4 = first;
          heap_push(heap, &heapSize, v4);
        }
        if ( second.freq > 0 )
        {
          v5 = second;
          heap_push(heap, &heapSize, v5);
        }
      }
      if ( heapSize > 0 )
      {
        ch = heap_pop(heap, &heapSize).ch;
        v7 = pos++;
        result[v7] = ch;
      }
      result[pos] = 0;
      return result;
    }
    else
    {
      empty_0 = (char *)malloc(1uLL);
      if ( empty_0 )
        *empty_0 = 0;
      return empty_0;
    }
  }
  else
  {
    empty = (char *)malloc(1uLL);
    if ( empty )
      *empty = 0;
    return empty;
  }
}