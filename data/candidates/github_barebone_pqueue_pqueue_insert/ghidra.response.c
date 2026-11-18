int pqueue_insert(pqueue_t *q,void *d)

{
  size_t sVar1;
  void **ppvVar2;
  size_t newsize;
  size_t i;
  void *tmp;
  void *d_local;
  pqueue_t *q_local;
  int local_c;
  
  if (q == (pqueue_t *)0x0) {
    local_c = 1;
  }
  else {
    if (q->avail <= q->size) {
      sVar1 = q->size + q->step;
      ppvVar2 = realloc(q->d,sVar1 * 8);
      if (ppvVar2 == (void **)0x0) {
        return 1;
      }
      q->d = ppvVar2;
      q->avail = sVar1;
    }
    sVar1 = q->size;
    q->size = sVar1 + 1;
    q->d[sVar1] = d;
    bubble_up(q,sVar1);
    local_c = 0;
  }
  return local_c;
}