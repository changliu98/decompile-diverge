short __cdecl popPriorityQueue(int *size, short *queue)
{
  // Decrement the element count to pop the last element
  int top_index = --(*size);

  // Return the 16-bit value located at the top of the queue.
  // The scaling factor of 2 means it's indexing into a 32-bit (4-byte) spaced array.
  return queue[2 * top_index];
}