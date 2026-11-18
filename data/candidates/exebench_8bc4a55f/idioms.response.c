static short popPriorityQueue(int *size, struct _queue *queue)
{
  return queue->data[--(*size)];
}