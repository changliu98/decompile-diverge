void __cdecl snap_unsink(
        jit_State *J,
        GCtrace *T,
        ExitState *ex,
        SnapNo snapno,
        BloomFilter rfilt,
        IRIns *ir,
        TValue *o)
{
  GCtab *v7; // [rsp+10h] [rbp-C0h]
  TValue *val; // [rsp+18h] [rbp-B8h]
  TValue tmp; // [rsp+20h] [rbp-B0h] BYREF
  IRIns *irk; // [rsp+28h] [rbp-A8h]
  GCtab *t; // [rsp+30h] [rbp-A0h]
  IRIns *irlast; // [rsp+38h] [rbp-98h]
  IRIns *irs; // [rsp+40h] [rbp-90h]
  IRIns *ira; // [rsp+48h] [rbp-88h]
  BloomFilter rfilta; // [rsp+50h] [rbp-80h]
  SnapNo snapnoa; // [rsp+5Ch] [rbp-74h]
  ExitState *exa; // [rsp+60h] [rbp-70h]
  GCtrace *Ta; // [rsp+68h] [rbp-68h]
  jit_State *Ja; // [rsp+70h] [rbp-60h]
  GCtab *v20; // [rsp+78h] [rbp-58h]
  TValue *v21; // [rsp+80h] [rbp-50h]
  lua_State *L; // [rsp+88h] [rbp-48h]
  uint32_t v23; // [rsp+94h] [rbp-3Ch]
  GCtab *v24; // [rsp+98h] [rbp-38h]
  TValue *v25; // [rsp+A0h] [rbp-30h]
  lua_State *v26; // [rsp+A8h] [rbp-28h]
  IRIns *v27; // [rsp+B0h] [rbp-20h]
  IRIns *iraa; // [rsp+B8h] [rbp-18h]
  GCtrace *v29; // [rsp+C0h] [rbp-10h]

  Ja = J;
  Ta = T;
  exa = ex;
  snapnoa = snapno;
  rfilta = rfilt;
  ira = ir;
  if ( ir->o == 78 )
    v7 = lj_tab_new(Ja->L, ira->op1, ira->op2);
  else
    v7 = lj_tab_dup(Ja->L, (const GCtab *)Ta->ir[ira->op1].op12);
  t = v7;
  L = Ja->L;
  v21 = o;
  v20 = v7;
  v26 = L;
  v25 = o;
  v24 = v7;
  v23 = -12;
  o->gcr.gcptr32 = (unsigned int)v7;
  v25->it = v23;
  irlast = &Ta->ir[Ta->snap[snapnoa].ref];
  for ( irs = ira + 1; irs < irlast; ++irs )
  {
    if ( irs->r == 254 )
    {
      v29 = Ta;
      iraa = ira;
      v27 = irs;
      if ( irs->s == 255 ? snap_sunk_store2(v29, iraa, v27) : &iraa[v27->s] == v27 )
      {
        irk = &Ta->ir[irs->op1];
        if ( irk->o == 62 )
        {
          if ( irk->op2 == 3 )
          {
            snap_restoreval(Ja, Ta, exa, snapnoa, rfilta, irs->op2, &tmp);
            t->metatable.gcptr32 = tmp.gcr.gcptr32;
          }
        }
        else
        {
          irk = &Ta->ir[irk->op2];
          if ( irk->o == 29 )
            irk = &Ta->ir[irk->op1];
          lj_ir_kvalue(Ja->L, &tmp, irk);
          val = lj_tab_set(Ja->L, t, &tmp);
          snap_restoreval(Ja, Ta, exa, snapnoa, rfilta, irs->op2, val);
        }
      }
    }
  }
}