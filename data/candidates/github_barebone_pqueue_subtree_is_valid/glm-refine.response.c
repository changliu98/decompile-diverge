int __cdecl subtree_is_valid(pqueue_t *q, int pos)
{
  pqueue_cmp_pri_f cmppri = q->cmppri;
  pqueue_pri_t pri_parent = q->getpri(q->d[pos]);

  // Check left child (2 * pos)
  if (2 * pos < q->size)
  {
    pqueue_pri_t pri_left = q->getpri(q->d[2 * pos]);
    if (!cmppri(pri_parent, pri_left))
      return 0;
    if (!subtree_is_valid(q, 2 * pos))
      return 0;
  }

  // Check right child (2 * pos + 1)
  if (2 * pos + 1 < q->size)
  {
    pqueue_pri_t pri_right = q->getpri(q->d[2 * pos + 1]);
    if (!cmppri(pri_parent, pri_right))
      return 0;
    if (!subtree_is_valid(q, 2 * pos + 1))
      return 0;
  }

  return 1;
}