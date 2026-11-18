void __cdecl cc_pqueue_heapify(CC_PQueue *pq, size_t index)
{
  void *swap_tmp; // [rsp+8h] [rbp-48h]
  void *indexPtr; // [rsp+10h] [rbp-40h]
  void *right; // [rsp+18h] [rbp-38h]
  void *left; // [rsp+20h] [rbp-30h]
  size_t indexa; // [rsp+40h] [rbp-10h]

  indexa = index;
  if ( pq->size > 1 )
  {
    left = pq->buffer[2 * index + 1];
    right = pq->buffer[2 * index + 2];
    indexPtr = pq->buffer[index];
    if ( 2 * index + 1 < pq->size && pq->cmp(indexPtr, left) < 0 )
    {
      indexPtr = left;
      indexa = 2 * index + 1;
    }
    if ( 2 * index + 2 < pq->size && pq->cmp(indexPtr, right) < 0 )
      indexa = 2 * index + 2;
    if ( indexa != index )
    {
      swap_tmp = pq->buffer[index];
      pq->buffer[index] = pq->buffer[indexa];
      pq->buffer[indexa] = swap_tmp;
      cc_pqueue_heapify(pq, indexa);
    }
  }
}