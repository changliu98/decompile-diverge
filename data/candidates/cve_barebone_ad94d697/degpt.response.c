void ubik_print(netdissect_options *ndo,u_char *bp)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  netdissect_options *pnVar2;
  uint32_t uVar3;
  uint32_t uVar4;
  char *pcVar5;
  tm *__tp;
  undefined *puVar6;
  int32_t counter_9;
  int32_t epoch_9;
  int32_t counter_8;
  int32_t epoch_8;
  int32_t counter_7;
  int32_t epoch_7;
  int _i_10;
  int _i_9;
  int32_t counter_6;
  int32_t epoch_6;
  int32_t counter_5;
  int32_t epoch_5;
  int _i_8;
  int _i_7;
  int _i_6;
  int _i_5;
  int _i_4;
  int32_t counter_4;
  int32_t epoch_4;
  int _i_3;
  int _i_2;
  int _i_1;
  int32_t counter_3;
  int32_t epoch_3;
  int32_t counter_2;
  int32_t epoch_2;
  unsigned_long _i;
  int32_t counter_1;
  int32_t epoch_1;
  int32_t counter;
  int32_t epoch;
  char str [256];
  tm *tm;
  time_t _t;
  int32_t temp;
  int ubik_op;
  u_char *bp_local;
  netdissect_options *ndo_local;
  
  bp_local = bp;
  ndo_local = ndo;
  ubik_op = EXTRACT_32BITS(bp + 0x1c);
  pnVar2 = ndo_local;
  p_Var1 = ndo_local->ndo_printf;
  pcVar5 = tok2str(ubik_req,"op#%d",ubik_op);
  (*p_Var1)(pnVar2," ubik call %s",pcVar5);
  bp_local = bp_local + 0x20;
  if (ubik_op == 10000) {
    if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
       (bp_local <= ndo_local->ndo_snapend + -4)) {
      temp = EXTRACT_32BITS(bp_local);
      bp_local = bp_local + 4;
      puVar6 = &DAT_00103083;
      if (temp != 0) {
        puVar6 = &DAT_0010307f;
      }
      (*ndo_local->ndo_printf)(ndo_local," syncsite %s",puVar6);
      (*ndo_local->ndo_printf)(ndo_local," votestart");
      if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
         (bp_local <= ndo_local->ndo_snapend + -4)) {
        uVar3 = EXTRACT_32BITS(bp_local);
        _t = (time_t)uVar3;
        bp_local = bp_local + 4;
        __tp = localtime(&_t);
        strftime(str,0x100,"%Y/%m/%d %H:%M:%S",__tp);
        (*ndo_local->ndo_printf)(ndo_local," %s",str);
        (*ndo_local->ndo_printf)(ndo_local," dbversion");
        if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
           (bp_local <= ndo_local->ndo_snapend + -8)) {
          uVar3 = EXTRACT_32BITS(bp_local);
          bp_local = bp_local + 4;
          uVar4 = EXTRACT_32BITS(bp_local);
          bp_local = bp_local + 4;
          (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
          (*ndo_local->ndo_printf)(ndo_local," tid");
          if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
             (bp_local <= ndo_local->ndo_snapend + -8)) {
            uVar3 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            uVar4 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
            return;
          }
        }
      }
    }
  }
  else if (ubik_op == 0x2713) {
    (*ndo_local->ndo_printf)(ndo_local," site");
    if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
       (bp_local <= ndo_local->ndo_snapend + -4)) {
      uVar3 = EXTRACT_32BITS(bp_local);
      bp_local = bp_local + 4;
      (*ndo_local->ndo_printf)(ndo_local," %lu",(ulong)uVar3);
      return;
    }
  }
  else {
    if (1 < ubik_op - 20000U) {
      if (ubik_op == 0x4e22) {
        (*ndo_local->ndo_printf)(ndo_local," tid");
        if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
           (bp_local <= ndo_local->ndo_snapend + -8)) {
          uVar3 = EXTRACT_32BITS(bp_local);
          bp_local = bp_local + 4;
          uVar4 = EXTRACT_32BITS(bp_local);
          bp_local = bp_local + 4;
          (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
          (*ndo_local->ndo_printf)(ndo_local," file");
          if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
             (bp_local <= ndo_local->ndo_snapend + -4)) {
            uVar3 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
            (*ndo_local->ndo_printf)(ndo_local," pos");
            if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
               (bp_local <= ndo_local->ndo_snapend + -4)) {
              uVar3 = EXTRACT_32BITS(bp_local);
              bp_local = bp_local + 4;
              (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
              (*ndo_local->ndo_printf)(ndo_local," length");
              if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
                 (bp_local <= ndo_local->ndo_snapend + -4)) {
                uVar3 = EXTRACT_32BITS(bp_local);
                bp_local = bp_local + 4;
                (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
                temp = EXTRACT_32BITS(bp_local);
                bp_local = bp_local + 4;
                tok2str(ubik_lock_types,"type %d",temp);
                return;
              }
            }
          }
        }
        goto LAB_001025d2;
      }
      if (ubik_op == 0x4e23) {
        (*ndo_local->ndo_printf)(ndo_local," tid");
        if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
           (bp_local <= ndo_local->ndo_snapend + -8)) {
          uVar3 = EXTRACT_32BITS(bp_local);
          bp_local = bp_local + 4;
          uVar4 = EXTRACT_32BITS(bp_local);
          bp_local = bp_local + 4;
          (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
          (*ndo_local->ndo_printf)(ndo_local," file");
          if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
             (bp_local <= ndo_local->ndo_snapend + -4)) {
            uVar3 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
            (*ndo_local->ndo_printf)(ndo_local," pos");
            if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
               (bp_local <= ndo_local->ndo_snapend + -4)) {
              uVar3 = EXTRACT_32BITS(bp_local);
              bp_local = bp_local + 4;
              (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
              return;
            }
          }
        }
        goto LAB_001025d2;
      }
      if (ubik_op == 0x4e25) {
        (*ndo_local->ndo_printf)(ndo_local," file");
        if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
           (bp_local <= ndo_local->ndo_snapend + -4)) {
          uVar3 = EXTRACT_32BITS(bp_local);
          bp_local = bp_local + 4;
          (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
          return;
        }
        goto LAB_001025d2;
      }
      if (ubik_op == 0x4e26) {
        (*ndo_local->ndo_printf)(ndo_local," file");
        if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
           (bp_local <= ndo_local->ndo_snapend + -4)) {
          uVar3 = EXTRACT_32BITS(bp_local);
          bp_local = bp_local + 4;
          (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
          (*ndo_local->ndo_printf)(ndo_local," length");
          if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
             (bp_local <= ndo_local->ndo_snapend + -4)) {
            uVar3 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
            (*ndo_local->ndo_printf)(ndo_local," dbversion");
            if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
               (bp_local <= ndo_local->ndo_snapend + -8)) {
              uVar3 = EXTRACT_32BITS(bp_local);
              bp_local = bp_local + 4;
              uVar4 = EXTRACT_32BITS(bp_local);
              bp_local = bp_local + 4;
              (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
              return;
            }
          }
        }
        goto LAB_001025d2;
      }
      if (1 < ubik_op - 0x4e27U) {
        if (ubik_op == 0x4e29) {
          (*ndo_local->ndo_printf)(ndo_local," tid");
          if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
             (bp_local <= ndo_local->ndo_snapend + -8)) {
            uVar3 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            uVar4 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
            (*ndo_local->ndo_printf)(ndo_local," file");
            if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
               (bp_local <= ndo_local->ndo_snapend + -4)) {
              uVar3 = EXTRACT_32BITS(bp_local);
              bp_local = bp_local + 4;
              (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
              (*ndo_local->ndo_printf)(ndo_local," length");
              if ((ndo_local->ndo_snapend + -4 <= ndo_local->ndo_snapend) &&
                 (bp_local <= ndo_local->ndo_snapend + -4)) {
                uVar3 = EXTRACT_32BITS(bp_local);
                bp_local = bp_local + 4;
                (*ndo_local->ndo_printf)(ndo_local," %d",(ulong)uVar3);
                return;
              }
            }
          }
          goto LAB_001025d2;
        }
        if (ubik_op != 0x4e2a) {
          if (ubik_op != 0x4e2c) {
            return;
          }
          (*ndo_local->ndo_printf)(ndo_local," tid");
          if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
             (bp_local <= ndo_local->ndo_snapend + -8)) {
            uVar3 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            uVar4 = EXTRACT_32BITS(bp_local);
            bp_local = bp_local + 4;
            (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
            (*ndo_local->ndo_printf)(ndo_local," oldversion");
            if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
               (bp_local <= ndo_local->ndo_snapend + -8)) {
              uVar3 = EXTRACT_32BITS(bp_local);
              bp_local = bp_local + 4;
              uVar4 = EXTRACT_32BITS(bp_local);
              bp_local = bp_local + 4;
              (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
              (*ndo_local->ndo_printf)(ndo_local," newversion");
              if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
                 (bp_local <= ndo_local->ndo_snapend + -8)) {
                uVar3 = EXTRACT_32BITS(bp_local);
                bp_local = bp_local + 4;
                uVar4 = EXTRACT_32BITS(bp_local);
                bp_local = bp_local + 4;
                (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
                return;
              }
            }
          }
          goto LAB_001025d2;
        }
      }
    }
    (*ndo_local->ndo_printf)(ndo_local," tid");
    if ((ndo_local->ndo_snapend + -8 <= ndo_local->ndo_snapend) &&
       (bp_local <= ndo_local->ndo_snapend + -8)) {
      uVar3 = EXTRACT_32BITS(bp_local);
      bp_local = bp_local + 4;
      uVar4 = EXTRACT_32BITS(bp_local);
      bp_local = bp_local + 4;
      (*ndo_local->ndo_printf)(ndo_local," %d.%d",(ulong)uVar3,(ulong)uVar4);
      return;
    }
  }
LAB_001025d2:
  (*ndo_local->ndo_printf)(ndo_local," [|ubik]");
  return;
}