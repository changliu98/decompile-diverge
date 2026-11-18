static short dequeue(int *size, struct _queue *queue)
{
  return queue->data[--(*size)];
}