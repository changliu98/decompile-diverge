void __cdecl func0(int *heap, int n, int a, int *outHeap)
{
  int i; // [rsp+4h] [rbp-1Ch]

  buildHeap(heap, n);
  if ( a >= *heap )
  {
    *heap = a;
    heapify(heap, n, 0);
    for ( i = 0; i < n; ++i )
      outHeap[i] = heap[i];
  }
}