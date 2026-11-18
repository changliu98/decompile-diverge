int __cdecl pqueue_insert(pqueue_t *q, void *d)
{
  size_t v2; // rax
  size_t newsize; // [rsp+0h] [rbp-30h]
  void **tmp; // [rsp+10h] [rbp-20h]

  if ( q )
  {
    if ( q->size >= q->avail )
    {
      newsize = q->step + q->size;
      tmp = (void **)realloc(q->d, 8 * newsize);
      if ( !tmp )
        return 1;
      q->d = tmp;
      q->avail = newsize;
    }
    v2 = q->size++;
    q->d[v2] = d;
    bubble_up(q, v2);
    return 0;
  }
  return 1;
}