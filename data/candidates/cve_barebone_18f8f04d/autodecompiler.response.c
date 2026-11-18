static void snap_unsink(jit_State *J, SnapShot *snap, SnapEntry *map,
          MSize n, MSize nent, IRIns *ir)
{
  GCtab *t = (((ir->op1 & 0xff00) == (0x0e<<8)) ? lj_tab_new(J->L, ((IRIns *)(((ir)-((ir)->op1 & 0xffff))))->op1, ((IRIns *)(((ir)-((ir)->op1 & 0xffff))))->op2) : lj_tab_dup(J->L, snap->ref[snap->map[n].key]));
  TValue tmp, *top;
  SnapEntry *next, *end = &snap->map[snap->len];
  for (next = &map[n]; next < end; next++) {
    if (((next)->val == (0xfffe << 16))) {
      int sink = (next+1 < end && ((next+1)->val == (0xffff << 16)) &&
    (next+2 >= end || (next+2)->val != (0xffff << 16)));
      if (sink) {
 IRIns *store = &snap->ref[next->key];
 if (((store)->t.irt == (IRT_NUM|IRT_NUM))) {
   lua_Number num;
   switch (((IRIns *)(((store)-((store)->op1 & 0xffff))))->o) {
   case IR_ADDOVF: case IR_SUBOVF: case IR_MULOVF:
     num = (lua_Number)((int32_t)next[1].key);
     break;
   case IR_DIVOVF: case IR_REDOVF:
     num = (lua_Number)((int32_t)next[1].key);
     break;
   default:
     num = (lua_Number)((int32_t)next[1].key);
     break;
   }
   (&tmp)->n = num;
 } else {
   store = &snap->ref[((IRIns *)(((store)-((store)->op1 & 0xffff))))->op2];
   if (((store)->t.irt == (IRT_NUM|IRT_NUM))) {
     lua_Number num = (lua_Number)((int32_t)store->op1);
     if (((IRIns *)(((store)-((store)->op1 & 0xffff))))->o == IR_DIVOVF)
       num /= (lua_Number)((int32_t)store->op2);
     (&tmp)->n = num;
   } else {
     store = &snap->ref[store->op1];
     if (((store)->t.irt == (IRT_NUM|IRT_NUM))) {
       lua_Number num = (lua_Number)((int32_t)store->op1);
       if (((IRIns *)(((store)-((store)->op1 & 0xffff))))->o == IR_DIVOVF)
  num /= (lua_Number)((int32_t)store->op2);
       (&tmp)->n = num;
     } else {
       store = &snap->ref[store->op2];
       (&tmp)->n = (lua_Number)((int32_t)store->op1);
     }
   }
 }
 continue;
      }
    }
    if (((next)->val == (0xfffd << 16))) {
      top = &t->metatable->gctv;
      goto setmeta;
    }
    if (((next)->val == (0xfffc << 16))) {
      top = &t->metatable->gctv;
      goto setmt;
    }
    if (((next)->val == (0xfffb << 16))) {
      top = &t->metatable->gctv;
      goto setmt;
    }
    if (((next)->val == (0xfffa << 16))) {
      top = &t->metatable->gctv;
      goto setmt;
    }
    if (((next)->val == (0xfff9 << 16))) {
      top = &t->metatable->gctv;
      goto setmt;
    }
    if (((next)->val == (0xfff8 << 16))) {
      top = &t->metatable->gctv;
      goto setmt;
lsetmt: lj_tab_set(J->L, t, &tmp);
      continue;
    }
    if (((next)->val == (0xffd2 << 16))) {
      top = &t->metatable->gctv;
      goto lsetmt;
    }
    if (((next)->val == (0xffd1 << 16))) {
      top = &t->metatable->gctv;
      goto lsetmt;
    }
    if (((next)->val == (0xffd0 << 16))) {
      top = &t->metatable->gctv;
      goto lsetmt;
lsetmt: lj_tab_set(J->L, t, &tmp);
      continue;
    }
    if (((next)->val == (0xffcf << 16))) {
      top = &t->metatable->gctv;
      goto lsetmt;
lsetmt: lj_tab_set(J->L, t, &tmp);
      continue;
    }
    if (((next)->val == (0xffce << 16))) {
      top = &t->metatable->gctv;
      goto lsetmt;
lsetmt: lj_tab_set(J->L, t, &tmp);
      continue;
    }
    if (((next)->val == (0xffcd << 16))) {
      top = &t->metatable->gctv;
      goto lsetmt;
lsetmt: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
    }
    if (((next)->val == (0xffcc << 16))) {
      top = &t->metatable->gctv;
      goto lsetmt2;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
    }
    if (((next)->val == (0xffcb << 16))) {
      top = &t->metatable->gctv;
      goto lsetmt2;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continuelsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continuelsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continuelsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continuelsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continuelsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continuelsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continuelsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continuelsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp)lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp)lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp)lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp)lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp)lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp)lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp)lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
lsetmt2: lj_tab_set(J->L, t, &tmp)lsetmt2: lj_tab_set(J->L, t, &tmp);
      continue;
l