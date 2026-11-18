static int subtree_is_valid(struct pqueue *q, int pos)
{
  if (2 * pos < q->size) {
    int (*cmppri)(void *, void *) = q->cmppri;
    void *item = q->d[pos];
    void *left = q->d[2 * pos];
    if (cmppri(q->getpri(item), q->getpri(left)))
      return 0;
    if (!subtree_is_valid(q, 2 * pos))
      return 0;
  }
  if (2 * pos + 1 < q->size) {
    int (*cmppri)(void *, void *) = q->cmppri;
    void *item = q->d[pos];
    void *right = q->d[2 * pos + 1];
    if (cmppri(q->getpri(item), q->getpri(right)))
      return 0;
    if (!subtree_is_valid(q, 2 * pos + 1))
      return 0;
  }
  return 1;
}