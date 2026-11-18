void snap_unsink(jit_State *J, GCtrace *T, ExitState *ex,
			SnapNo snapno, BloomFilter rfilt, IRIns *ir, TValue *o)
{
  GCtab *t = (ir->o == (uint8_t)'\210') ?
	lj_tab_new(J->L, ir->op1, ir->op2) :
	lj_tab_dup(J->L, T->ir[ir->op1].op1);
  ((o)->it = (int32_t)(-12));
  ((o)->gcr = (GCRef)((GCobj *)(uintptr_t)(t)));
  IRIns *iref = T->ir + T->snap[snapno].ref;
  for (IRIns *irp = ir+1; irp < iref; irp++) {
    if ((0 && (irp)->line != (uint16_t)~0) || (irp)->line == (uint16_t)~2) {
      IRIns *irr = T->ir + (irp->op1);
      if ((irr->o == (uint8_t)'>')) {
	if (irp->op2 == 3) {
	  TValue tmp;
	  snap_restoreval(J, T, ex, snapno, rfilt, irp->op2, &tmp);
	  t->metatable = tmp.gcr;
	}
      } else {
	TValue key;
	IRIns *irk = T->ir + (irr->op2);
	if ((irk->o == (uint8_t)'\035')) irk = T->ir + (irk->op1);
	lj_ir_kvalue(J->L, &key, irk);
	TValue *val = lj_tab_set(J->L, t, &key);
	snap_restoreval(J, T, ex, snapno, rfilt, irp->op2, val);
      }
    }
  }
}