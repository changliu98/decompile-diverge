void __cdecl func0(int *arr, int length)
{
  int temp;
  int end;

  heapify(arr, length);
  
  for (end = length - 1; end > 0; )
  {
    // Swap the root (maximum element) with the last element of the current heap
    temp = arr[end];
    arr[end] = arr[0];
    arr[0] = temp;

    // Reduce the heap size and restore the max-heap property
    --end;
    shift_down(arr, 0, end);
  }
}