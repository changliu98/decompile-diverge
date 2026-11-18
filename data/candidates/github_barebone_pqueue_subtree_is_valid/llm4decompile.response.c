int subtree_is_valid(pqueue_t *q, size_t pos)
{
  if(2*pos < q->size) {
    if(q->cmppri(q->getpri(q->d[pos]), q->getpri(q->d[2*pos])) != 0)
      return 0;
    if(!subtree_is_valid(q, 2*pos))
      return 0;
  }
  if(2*pos+1 < q->size) {
    if(q->cmppri(q->getpri(q->d[pos]), q->getpri(q->d[2*pos+1])) != 0)
      return 0;
    if(!subtree_is_valid(q, 2*pos+1))
      return 0;
  }
  return 1;
}