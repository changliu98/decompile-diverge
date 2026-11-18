void func0(int *heap, int n, int a, int *outHeap)
{
  int i;
  buildHeap(heap, n);
  if (heap[0] > a)
    return;
  heap[0] = a;
  heapify(heap, n, 0);
  for (i = 0; i < n; i++)
    outHeap[i] = heap[i];
}