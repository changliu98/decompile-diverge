void snap_unsink(jit_State *J, GCtab *kt, SnapShot *snap, int32_t nent, BCIns *pc, SnapEntry *sn) {
    lua_State *L = J->L;
    GCtab *t;
    TValue o;

    if (sn->type == 0x4e) {
        t = lj_tab_new(L, sn->offset, sn->unused);
    } else {
        t = lj_tab_dup(L, kt);
    }

    o.it = 0xfffffff4; // Set TValue tag (e.g. nil/table tag)
    o.gcr = (GCobj *)t;

    IRRef *ir_base = J->ir;
    SnapEntry *sn_end = sn + J->nins; // Assuming J->nins is at offset 0x10

    for (; sn < sn_end; sn++) {
        if (sn->op != 0xfe) {
            continue;
        }

        int is_sunk = 0;
        if (sn->arg == 0xff) {
            is_sunk = 1;
        } else {
            IRRef *ir_arg = (IRRef *)((uint8_t *)J + (sn->arg << 3));
            if (ir_arg == (IRRef *)sn) {
                is_sunk = 1;
            }
        }

        if (!is_sunk) {
            continue;
        }

        IRRef *ir = (IRRef *)((uint8_t *)ir_base + (sn->offset << 3));

        if (ir->type == 0x3e) {
            if (ir->size == 3) {
                snap_restoreval(J, ir, snap, nent, sn, &o);
                t->array[ir->hmask] = o; // Assuming array is at offset 0x10
            }
        } else {
            if (ir->type == 0x1d) {
                ir = (IRRef *)((uint8_t *)ir_base + (ir->size << 3));
                ir = (IRRef *)((uint8_t *)ir_base + (ir->offset << 3));
            }

            TValue key;
            lj_ir_kvalue(L, &key, ir);
            TValue *slot = lj_tab_set(L, t, &key);
            snap_restoreval(J, ir, snap, nent, sn, slot);
        }
    }
}