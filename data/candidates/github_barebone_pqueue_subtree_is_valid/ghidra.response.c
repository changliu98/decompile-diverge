int subtree_is_valid(pqueue_t *q,int pos)

{
  pqueue_cmp_pri_f p_Var1;
  int iVar2;
  pqueue_pri_t pVar3;
  pqueue_pri_t pVar4;
  int pos_local;
  pqueue_t *q_local;
  
  if ((ulong)(long)(pos << 1) < q->size) {
    p_Var1 = q->cmppri;
    pVar3 = (*q->getpri)(q->d[pos]);
    pVar4 = (*q->getpri)(q->d[pos << 1]);
    iVar2 = (*p_Var1)(pVar3,pVar4);
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = subtree_is_valid(q,pos << 1);
    if (iVar2 == 0) {
      return 0;
    }
  }
  if ((ulong)(long)(pos * 2 + 1) < q->size) {
    p_Var1 = q->cmppri;
    pVar3 = (*q->getpri)(q->d[pos]);
    pVar4 = (*q->getpri)(q->d[pos * 2 + 1]);
    iVar2 = (*p_Var1)(pVar3,pVar4);
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = subtree_is_valid(q,pos * 2 + 1);
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}