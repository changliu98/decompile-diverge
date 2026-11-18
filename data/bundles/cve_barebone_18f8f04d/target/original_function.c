static void snap_unsink(jit_State *J, GCtrace *T, ExitState *ex,
			SnapNo snapno, BloomFilter rfilt,
			IRIns *ir, TValue *o)
{
  lua_assert(ir->o == IR_TNEW || ir->o == IR_TDUP ||
	     ir->o == IR_CNEW || ir->o == IR_CNEWI);
#if LJ_HASFFI
  if (ir->o == IR_CNEW || ir->o == IR_CNEWI) {
    CTState *cts = ctype_cts(J->L);
    CTypeID id = (CTypeID)T->ir[ir->op1].i;
    CTSize sz = lj_ctype_size(cts, id);
    GCcdata *cd = lj_cdata_new(cts, id, sz);
    setcdataV(J->L, o, cd);
    if (ir->o == IR_CNEWI) {
      uint8_t *p = (uint8_t *)cdataptr(cd);
      lua_assert(sz == 4 || sz == 8);
      if (LJ_32 && sz == 8 && ir+1 < T->ir + T->nins && (ir+1)->o == IR_HIOP) {
	snap_restoredata(T, ex, snapno, rfilt, (ir+1)->op2, LJ_LE?p+4:p, 4);
	if (LJ_BE) p += 4;
	sz = 4;
      }
      snap_restoredata(T, ex, snapno, rfilt, ir->op2, p, sz);
    } else {
      IRIns *irs, *irlast = &T->ir[T->snap[snapno].ref];
      for (irs = ir+1; irs < irlast; irs++)
	if (irs->r == RID_SINK && snap_sunk_store(T, ir, irs)) {
	  IRIns *iro = &T->ir[T->ir[irs->op1].op2];
	  uint8_t *p = (uint8_t *)cd;
	  CTSize szs;
	  lua_assert(irs->o == IR_XSTORE && T->ir[irs->op1].o == IR_ADD);
	  lua_assert(iro->o == IR_KINT || iro->o == IR_KINT64);
	  if (irt_is64(irs->t)) szs = 8;
	  else if (irt_isi8(irs->t) || irt_isu8(irs->t)) szs = 1;
	  else if (irt_isi16(irs->t) || irt_isu16(irs->t)) szs = 2;
	  else szs = 4;
	  if (LJ_64 && iro->o == IR_KINT64)
	    p += (int64_t)ir_k64(iro)->u64;
	  else
	    p += iro->i;
	  lua_assert(p >= (uint8_t *)cdataptr(cd) &&
		     p + szs <= (uint8_t *)cdataptr(cd) + sz);
	  if (LJ_32 && irs+1 < T->ir + T->nins && (irs+1)->o == IR_HIOP) {
	    lua_assert(szs == 4);
	    snap_restoredata(T, ex, snapno, rfilt, (irs+1)->op2, LJ_LE?p+4:p,4);
	    if (LJ_BE) p += 4;
	  }
	  snap_restoredata(T, ex, snapno, rfilt, irs->op2, p, szs);
	}
    }
  } else
#endif
  {
    IRIns *irs, *irlast;
    GCtab *t = ir->o == IR_TNEW ? lj_tab_new(J->L, ir->op1, ir->op2) :
				  lj_tab_dup(J->L, ir_ktab(&T->ir[ir->op1]));
    settabV(J->L, o, t);
    irlast = &T->ir[T->snap[snapno].ref];
    for (irs = ir+1; irs < irlast; irs++) {
      if (irs->r == RID_SINK && snap_sunk_store(T, ir, irs)) {
	IRIns *irk = &T->ir[irs->op1];
	TValue tmp, *val;
	lua_assert(irs->o == IR_ASTORE || irs->o == IR_HSTORE ||
		   irs->o == IR_FSTORE);
	if (irk->o == IR_FREF) {
	  switch (irk->op2) {
	  case IRFL_TAB_META:
	    snap_restoreval(J, T, ex, snapno, rfilt, irs->op2, &tmp);
	    /* NOBARRIER: The table is new (marked white). */
	    setgcref(t->metatable, obj2gco(tabV(&tmp)));
	    break;
	  case IRFL_TAB_NOMM:
	    /* Negative metamethod cache invalidated by lj_tab_set() below. */
	    break;
	  default:
	    lua_assert(0);
	    break;
	  }
	} else {
	  irk = &T->ir[irk->op2];
	  if (irk->o == IR_KSLOT) irk = &T->ir[irk->op1];
	  lj_ir_kvalue(J->L, &tmp, irk);
	  val = lj_tab_set(J->L, t, &tmp);
	  /* NOBARRIER: The table is new (marked white). */
	  snap_restoreval(J, T, ex, snapno, rfilt, irs->op2, val);
	  if (LJ_SOFTFP && irs+1 < T->ir + T->nins && (irs+1)->o == IR_HIOP) {
	    snap_restoreval(J, T, ex, snapno, rfilt, (irs+1)->op2, &tmp);
	    val->u32.hi = tmp.u32.lo;
	  }
	}
      }
    }
  }
}