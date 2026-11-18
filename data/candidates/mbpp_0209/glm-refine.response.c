void __cdecl func0(int *heap, int n, int a, int *outHeap)
{
  buildHeap(heap, n);
  
  // If the new element 'a' is greater than or equal to the current maximum (root of the max-heap)
  if (a >= heap[0])
  {
    // Replace the root with the new element
    heap[0] = a;
    
    // Restore the heap property
    heapify(heap, n, 0);
    
    // Copy the updated heap to the output array
    for (int i = 0; i < n; ++i)
    {
      outHeap[i] = heap[i];
    }
  }
}