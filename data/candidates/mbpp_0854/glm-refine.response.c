void __cdecl func0(int *heap, int size)
{
  int temp;
  int child;
  int parent;

  // Build a min-heap using Floyd's bottom-up heap construction algorithm.
  // Start from the last non-leaf node and sift down to the root.
  for ( parent = size / 2 - 1; parent >= 0; --parent )
  {
    // Sift down the element at 'parent' to its proper position in the min-heap
    for ( child = 2 * parent + 1; child < size; child = 2 * child + 1 )
    {
      // Find the smaller of the two children
      if ( child + 1 < size && heap[child] > heap[child + 1] )
        ++child;

      // If the parent is already smaller than or equal to the smallest child, 
      // the min-heap property is satisfied for this subtree.
      if ( heap[parent] <= heap[child] )
        break;

      // Otherwise, swap the parent with the smallest child and continue sifting down
      temp = heap[parent];
      heap[parent] = heap[child];
      heap[child] = temp;

      // Update the parent index for the next iteration. 
      // (child - 1 is used because the outer loop will decrement it by 1)
      parent = child - 1;
    }
  }
}