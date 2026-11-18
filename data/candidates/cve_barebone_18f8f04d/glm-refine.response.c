void __cdecl snap_unsink(
        jit_State *J,
        GCtrace *T,
        ExitState *ex,
        SnapNo snapno,
        BloomFilter rfilt,
        IRIns *ir,
        TValue *o)
{
  TValue tmp;
  IRIns *irk;
  IRIns *irlast;
  IRIns *irs;
  GCtab *t;
  lua_State *L = J->L;

  // Allocate or duplicate the table based on the IR instruction type
  if (ir->o == 78)
    t = lj_tab_new(L, ir->op1, ir->op2);
  else
    t = lj_tab_dup(L, (const GCtab *)T->ir[ir->op1].op12);

  // Initialize the output TValue as a table tag ( LJ_TTAB = ~11, which is -12 in signed 32-bit )
  o->gcr.gcptr32 = (unsigned int)t;
  o->it = -12;

  // Iterate over subsequent IR instructions until the end of the snapshot
  irlast = &T->ir[T->snap[snapno].ref];
  for (irs = ir + 1; irs < irlast; ++irs)
  {
    // Check if the instruction register is SUNK (254)
    if (irs->r == 254)
    {
      // Check if it's a sunk store or a self-reference
      if (irs->s == 255 ? snap_sunk_store2(T, ir, irs) : &ir[irs->s] == irs)
      {
        irk = &T->ir[irs->op1];

        // Check for metatable assignment (IR_EQ == 62, op2 == 3)
        if (irk->o == 62 && irk->op2 == 3)
        {
          snap_restoreval(J, T, ex, snapno, rfilt, irs->op2, &tmp);
          t->metatable.gcptr32 = tmp.gcr.gcptr32;
        }
        else
        {
          // Resolve key value
          irk = &T->ir[irk->op2];
          if (irk->o == 29) // IR_KKINT or similar constant load
            irk = &T->ir[irk->op1];

          lj_ir_kvalue(L, &tmp, irk);
          TValue *val = lj_tab_set(L, t, &tmp);
          snap_restoreval(J, T, ex, snapno, rfilt, irs->op2, val);
        }
      }
    }
  }
}