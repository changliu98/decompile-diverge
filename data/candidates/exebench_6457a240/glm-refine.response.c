void __cdecl peneira(int m, int *v)
{
  // 'p' tracks the parent index, 'f' tracks the child index
  int parent = 1;
  int child = 2;
  
  // Store the initial root element being sifted down
  int temp = v[1];

  // Loop while the child index is within the heap bounds
  while (child <= m)
  {
    // If the right child exists and is greater than the left child,
    // choose the right child for the potential swap
    if (child < m && v[child] < v[child + 1])
      child++;

    // If the parent's value is greater than or equal to the largest child, 
    // the max-heap property is satisfied; stop sifting down.
    if (temp >= v[child])
      break;

    // Move the larger child up to the parent's position
    v[parent] = v[child];

    // Update indices to move down the tree
    parent = child;
    child *= 2; // Left child of the next level
  }
  
  // Place the original root value into its final correct position
  v[parent] = temp;
}