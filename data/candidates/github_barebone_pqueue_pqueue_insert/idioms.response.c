int pqueue_insert(struct pqueue *q, void *d)
{
  if (q == ((void *)0))
    return 1;
  if (q->size >= q->avail) {
    void **tmp = (void **)realloc(q->d,
                                  sizeof(void *) * (q->step + q->size));
    if (tmp == ((void *)0))
      return 1;
    q->d = tmp;
    q->avail = q->step + q->size;
  }
  q->d[q->size++] = d;
  bubble_up(q, q->size - 1);
  return 0;
}