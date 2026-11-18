void func0(int *heap, int n, int k, int *out) {
    buildHeap(heap, n);
    
    if (k >= heap[0]) {
        heap[0] = k;
        heapify(heap, n, 0);
        
        for (int i = 0; i < n; i++) {
            out[i] = heap[i];
        }
    }
}