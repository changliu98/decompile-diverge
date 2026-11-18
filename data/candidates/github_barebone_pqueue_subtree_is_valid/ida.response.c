int __cdecl subtree_is_valid(pqueue_t *q, int pos)
{
  pqueue_pri_t v2; // rsi
  pqueue_pri_t v3; // rsi
  pqueue_pri_t v5; // [rsp+8h] [rbp-38h]
  pqueue_cmp_pri_f v6; // [rsp+10h] [rbp-30h]
  pqueue_pri_t v7; // [rsp+18h] [rbp-28h]
  pqueue_cmp_pri_f cmppri; // [rsp+20h] [rbp-20h]

  if ( 2 * pos >= q->size )
    goto LABEL_6;
  cmppri = q->cmppri;
  v7 = q->getpri(q->d[pos]);
  v2 = q->getpri(q->d[2 * pos]);
  if ( !cmppri(v7, v2) )
  {
    if ( !subtree_is_valid(q, 2 * pos) )
      return 0;
LABEL_6:
    if ( 2 * pos + 1 < q->size )
    {
      v6 = q->cmppri;
      v5 = q->getpri(q->d[pos]);
      v3 = q->getpri(q->d[2 * pos + 1]);
      if ( v6(v5, v3) )
        return 0;
      if ( !subtree_is_valid(q, 2 * pos + 1) )
        return 0;
    }
    return 1;
  }
  return 0;
}