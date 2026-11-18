void cc_pqueue_heapify(struct CC_PQueue *pq, unsigned long index)
{
  void *parent;
  void *left;
  void *right;
  void *tmp;
  unsigned long min;
  min = index;
  if (pq->size > 1) {
    left = pq->buffer[(min * 2) + 1];
    right = pq->buffer[(min * 2) + 2];
    parent = pq->buffer[min];
    if ((min * 2 + 1) < pq->size &&
        pq->cmp(parent, left) < 0) {
      parent = left;
      min = min * 2 + 1;
    }
    if ((min * 2 + 2) < pq->size &&
        pq->cmp(parent, right) < 0) {
      min = min * 2 + 2;
    }
    if (min != index) {
      tmp = pq->buffer[min];
      pq->buffer[min] = pq->buffer[index];
      pq->buffer[index] = tmp;
      cc_pqueue_heapify(pq, min);
    }
  }
}