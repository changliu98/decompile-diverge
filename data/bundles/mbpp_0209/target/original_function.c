void func0(int heap[], int n, int a, int* outHeap) {
  buildHeap(heap, n);
  if (a < heap[0]) return;
  heap[0] = a;
  heapify(heap, n, 0);
  for (int i = 0; i < n; i++) {
    outHeap[i] = heap[i];
  }
}