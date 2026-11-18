void func0(int *heap,int n,int a,int *outHeap)

{
  int i;
  int *outHeap_local;
  int a_local;
  int n_local;
  int *heap_local;
  
  buildHeap(heap,n);
  if (*heap <= a) {
    *heap = a;
    heapify(heap,n,0);
    for (i = 0; i < n; i = i + 1) {
      outHeap[i] = heap[i];
    }
  }
  return;
}