short __cdecl popPriorityQueue(int *size, short *queue)
{
  --*size;
  return queue[2 * *size];
}