void jitt_setfield(struct jit_State *J, struct GCtrace *T, struct ExitState *ex, unsigned int snapno, struct BloomFilter rfilt, struct IRIns *ir, struct TValue *o)
{
  struct TValue tmp; struct TValue *tmp2;
  struct IRIns *irlast; struct IRIns *ira; struct IRIns *irk;
  struct IRIns *irk1;
  struct GCtab *tab;
  struct GCtab *tab1;
  struct lua_State *L;
  struct TValue *val;
  unsigned int it;
  tab = ((ir->o == IR_GETTABUP) ? jitt_getupval(J->L, ir->op1, ir->op2) : jitt_gettab(J->L, T->ir[ir->op1].op12));
  L = J->L;
  val = o;
  tab1 = tab;
  tmp2 = o;
  tab = tab1;
  it = (LUA_T_ARRAY);
  val->gcr.gcptr32 = (unsigned int)tab;
  tmp2->it = it;
  irlast = &T->ir[T->snap[snapno].ref];
  for (ira = ir + 1; ira < irlast; ira++)
  {
    if (ira->r == IR_NEWTMP)
    {
      struct GCtrace *T1 = T;
      struct IRIns *ira1 = ir;
      struct IRIns *ira2 = ira + 1;
      if (ira2->s == IR_NEWTMP)
      {
        if (jitt_isloopvar(T1, ira1, ira2))
        {
          irk = &T->ir[ira->op1];
          if (irk->o == IR_LOOPVAR)
          {
            if (irk->op2 == IR_LOOPVAR1)
            {
              jitt_setloopvar(J, T, ex, snapno, rfilt, ira->op2, &tmp);
              tab->metatable.gcptr32 = (unsigned int)tmp.gcr.gcptr32;
            }
          }
          else
          {
            irk = &T->ir[irk->op2];
            if (irk->o == IR_LOOPVAR)
              irk = &T->ir[irk->op1];
            jitt_getloopvar(J->L, &tmp, irk);
            val = jitt_getval(J->L, tab, &tmp);
            jitt_setloopvar(J, T, ex, snapno, rfilt, ira->op2, val);
          }
        }
      }
    }
  }
}