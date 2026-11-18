void snap_unsink(jit_State *J,GCtrace *T,ExitState *ex,SnapNo snapno,BloomFilter rfilt,IRIns *ir,
                TValue *o)

{
  IRIns *pIVar1;
  IRIns *pIVar2;
  TValue *o_00;
  GCtab *local_c8;
  TValue *val;
  TValue tmp;
  IRIns *irk;
  GCtab *t;
  IRIns *irlast;
  IRIns *irs;
  IRIns *ir_local;
  BloomFilter rfilt_local;
  SnapNo snapno_local;
  ExitState *ex_local;
  GCtrace *T_local;
  jit_State *J_local;
  GCtab *local_60;
  TValue *local_58;
  lua_State *local_50;
  undefined4 local_44;
  GCtab *local_40;
  TValue *local_38;
  lua_State *local_30;
  IRIns *local_28;
  IRIns *local_20;
  GCtrace *local_18;
  uint local_c;
  
  ir_local = ir;
  rfilt_local = rfilt;
  snapno_local = snapno;
  ex_local = ex;
  T_local = T;
  J_local = J;
  if ((ir->field_1).o == 'N') {
    local_c8 = lj_tab_new(J->L,(uint)(ir->field_0).op1,(uint)(ir->field_0).op2);
  }
  else {
    local_c8 = lj_tab_dup(J->L,(GCtab *)(ulong)T->ir[(ir->field_0).op1].field_1.op12);
  }
  t = local_c8;
  local_50 = J_local->L;
  local_58 = o;
  local_60 = local_c8;
  local_38 = o;
  local_40 = local_c8;
  local_44 = 0xfffffff4;
  (o->u32).lo = (uint32_t)local_c8;
  (o->field_2).it = 0xfffffff4;
  irlast = T_local->ir + T_local->snap[snapno_local].ref;
  local_30 = local_50;
  pIVar2 = ir_local;
  while (pIVar1 = pIVar2, irs = pIVar1 + 1, irs < irlast) {
    pIVar2 = irs;
    if (*(char *)((long)pIVar1 + 0xe) == -2) {
      local_18 = T_local;
      local_20 = ir_local;
      local_28 = irs;
      if (*(char *)((long)pIVar1 + 0xf) == -1) {
        local_c = snap_sunk_store2(T_local,ir_local,irs);
      }
      else {
        local_c = (uint)(ir_local + (int)(uint)*(byte *)((long)pIVar1 + 0xf) == irs);
      }
      pIVar2 = irs;
      if (local_c != 0) {
        irk = T_local->ir + (irs->field_0).op1;
        if ((irk->field_1).o == '>') {
          pIVar2 = irs;
          if ((irk->field_0).op2 == 3) {
            snap_restoreval(J_local,T_local,ex_local,snapno_local,rfilt_local,
                            (uint)(irs->field_0).op2,&tmp);
            (t->metatable).gcptr32 = (uint32_t)tmp.field_2.field_0;
            pIVar2 = irs;
          }
        }
        else {
          irk = T_local->ir + (irk->field_0).op2;
          if ((irk->field_1).o == '\x1d') {
            irk = T_local->ir + (irk->field_0).op1;
          }
          lj_ir_kvalue(J_local->L,&tmp,irk);
          o_00 = lj_tab_set(J_local->L,t,&tmp);
          snap_restoreval(J_local,T_local,ex_local,snapno_local,rfilt_local,(uint)(irs->field_0).op2
                          ,o_00);
          pIVar2 = irs;
        }
      }
    }
  }
  return;
}