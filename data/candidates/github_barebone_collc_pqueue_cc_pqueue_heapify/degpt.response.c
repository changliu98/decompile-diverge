void cc_pqueue_heapify(CC_PQueue *pq,size_t index)

{
  void *pvVar1;
  void *pvVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  void *swap_tmp;
  void *indexPtr;
  void *right;
  void *left;
  size_t tmp;
  size_t R;
  size_t L;
  size_t index_local;
  CC_PQueue *pq_local;
  
  if (1 < pq->size) {
    uVar4 = index * 2 + 1;
    uVar5 = index * 2 + 2;
    pvVar1 = pq->buffer[uVar4];
    pvVar2 = pq->buffer[uVar5];
    indexPtr = pq->buffer[index];
    index_local = index;
    if ((uVar4 < pq->size) && (iVar3 = (*pq->cmp)(indexPtr,pvVar1), index_local = index, iVar3 < 0))
    {
      indexPtr = pvVar1;
      index_local = uVar4;
    }
    if ((uVar5 < pq->size) && (iVar3 = (*pq->cmp)(indexPtr,pvVar2), iVar3 < 0)) {
      index_local = uVar5;
    }
    if (index_local != index) {
      pvVar1 = pq->buffer[index];
      pq->buffer[index] = pq->buffer[index_local];
      pq->buffer[index_local] = pvVar1;
      cc_pqueue_heapify(pq,index_local);
    }
  }
  return;
}