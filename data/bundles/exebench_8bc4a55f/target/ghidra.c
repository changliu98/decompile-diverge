short popPriorityQueue(int *size,short *queue)

{
  short *queue_local;
  int *size_local;
  
  *size = *size + -1;
  return queue[*size << 1];
}