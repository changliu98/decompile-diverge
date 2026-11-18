static void snap_unsink(jit_State *J, SnapShot *snap, SnapEntry *ent, IRRef ref,
                        IRRef1 ref1, SnapEntry_op *op, TValue *o) {
  GCtab *t = (op->o == 78) ? lj_tab_new(J->L, op->op1, op->op2)
                           : lj_tab_dup(J->L, snap->ops[op->op1].val);
  o->u32.ptr = (uint32_t)(uintptr_t)t;
  o->it = (~12u);
  SnapEntry_op *end = snap->ops + snap->tree[ref].first;
  for (op++; op < end; op++) {
    if (op->sn == 254 &&
        (op->sn1 == 255 ? snap_sunk_store2(snap, op) : op == op + op->sn1)) {
      SnapEntry_op *op1 = snap->ops + op->op1;
      if (op1->o == 62) {
        if (op1->op2 == 3) {
          TValue key;
          snap_restoreval(J, snap, ent, ref, ref1, op->op2, &key);
          t->metatable = key.u32.ptr;
        }
      } else {
        TValue key;
        op1 = snap->ops + (op1->op2);
        if (op1->o == 29) op1 = snap->ops + op1->op1;
        lj_ir_kvalue(J->L, &key, op1);
        snap_restoreval(J, snap, ent, ref, ref1, op->op2,
                        lj_tab_set(J->L, t, &key));
      }
    }
  }
}