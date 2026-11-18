int isis_print_mt_capability_subtlv(netdissect_options *ndo,uint8_t *tptr,int len)

{
  byte bVar1;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var2;
  int iVar3;
  uint v;
  char *pcVar4;
  byte *pbVar5;
  int tmp;
  int stlv_len;
  int stlv_type;
  int len_local;
  uint8_t *tptr_local;
  netdissect_options *ndo_local;
  
  iVar3 = len;
  pbVar5 = tptr;
  while( true ) {
    do {
      while( true ) {
        tptr_local = pbVar5;
        len_local = iVar3;
        if (len_local < 3) {
          return 0;
        }
        v = (uint)*tptr_local;
        pbVar5 = tptr_local + 2;
        bVar1 = tptr_local[1];
        p_Var2 = ndo->ndo_printf;
        pcVar4 = tok2str(isis_mt_capability_subtlv_values,"unknown",v);
        (*p_Var2)(ndo,"\n\t      %s subTLV #%u, length: %u",pcVar4,(ulong)v,(ulong)(uint)bVar1);
        if (v != 1) break;
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -0x13) || (ndo->ndo_snapend + -0x13 < pbVar5))
        goto LAB_00101c3d;
        (*ndo->ndo_printf)(ndo,"\n\t        CIST Root-ID: %08x",
                           (ulong)((uint)*pbVar5 << 0x18 | (uint)tptr_local[3] << 0x10 |
                                   (uint)tptr_local[4] << 8 | (uint)tptr_local[5]));
        (*ndo->ndo_printf)(ndo," %08x",
                           (ulong)((uint)tptr_local[6] << 0x18 | (uint)tptr_local[7] << 0x10 |
                                   (uint)tptr_local[8] << 8 | (uint)tptr_local[9]));
        (*ndo->ndo_printf)(ndo,", Path Cost: %08x",
                           (ulong)((uint)tptr_local[10] << 0x18 | (uint)tptr_local[0xb] << 0x10 |
                                   (uint)tptr_local[0xc] << 8 | (uint)tptr_local[0xd]));
        (*ndo->ndo_printf)(ndo,", Prio: %d",(ulong)CONCAT11(tptr_local[0xe],tptr_local[0xf]));
        (*ndo->ndo_printf)(ndo,"\n\t        RES: %d",
                           (ulong)(uint)((int)(uint)CONCAT11(tptr_local[0x10],tptr_local[0x11]) >> 5
                                        ));
        (*ndo->ndo_printf)(ndo,", V: %d",
                           (ulong)((int)(uint)CONCAT11(tptr_local[0x10],tptr_local[0x11]) >> 4 & 1))
        ;
        (*ndo->ndo_printf)(ndo,", SPSource-ID: %d",
                           (ulong)((tptr_local[0x11] & 0xf) << 0x10 | (uint)tptr_local[0x12] << 8 |
                                  (uint)tptr_local[0x13]));
        pbVar5 = tptr_local + 0x14;
        (*ndo->ndo_printf)(ndo,", No of Trees: %x",(ulong)*pbVar5);
        tptr_local = tptr_local + 0x15;
        len_local = len_local + -0x15;
        for (tmp = (int)*pbVar5; iVar3 = len_local, pbVar5 = tptr_local, tmp != 0; tmp = tmp + -1) {
          if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < tptr_local))
          goto LAB_00101c3d;
          (*ndo->ndo_printf)(ndo,"\n\t         U:%d, M:%d, A:%d, RES:%d",
                             (ulong)(uint)((int)(uint)*tptr_local >> 7),
                             (ulong)((int)(uint)*tptr_local >> 6 & 1),
                             (ulong)((int)(uint)*tptr_local >> 5 & 1),(ulong)(*tptr_local & 0x1f));
          (*ndo->ndo_printf)(ndo,", ECT: %08x",
                             (ulong)((uint)tptr_local[1] << 0x18 | (uint)tptr_local[2] << 0x10 |
                                     (uint)tptr_local[3] << 8 | (uint)tptr_local[4]));
          (*ndo->ndo_printf)(ndo,", BVID: %d, SPVID: %d",
                             (ulong)(((uint)tptr_local[5] << 0x10 | (uint)tptr_local[6] << 8) >> 0xc
                                    ),(ulong)((tptr_local[6] & 0xf) << 8 | (uint)tptr_local[7]));
          tptr_local = tptr_local + 8;
          len_local = len_local + -8;
        }
      }
      iVar3 = len_local + -2;
    } while (v != 3);
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < pbVar5)) break;
    (*ndo->ndo_printf)(ndo,"\n\t        BMAC: %08x",
                       (ulong)((uint)*pbVar5 << 0x18 | (uint)tptr_local[3] << 0x10 |
                               (uint)tptr_local[4] << 8 | (uint)tptr_local[5]));
    (*ndo->ndo_printf)(ndo,"%04x",(ulong)CONCAT11(tptr_local[6],tptr_local[7]));
    (*ndo->ndo_printf)(ndo,", RES: %d, VID: %d",
                       (ulong)(uint)((int)(uint)CONCAT11(tptr_local[8],tptr_local[9]) >> 0xc),
                       (ulong)(CONCAT11(tptr_local[8],tptr_local[9]) & 0xfff));
    tptr_local = tptr_local + 10;
    len_local = len_local + -10;
    for (stlv_len = bVar1 - 8; iVar3 = len_local, pbVar5 = tptr_local, 3 < stlv_len;
        stlv_len = stlv_len + -4) {
      if ((ndo->ndo_snapend < ndo->ndo_snapend + -4) || (ndo->ndo_snapend + -4 < tptr_local))
      goto LAB_00101c3d;
      (*ndo->ndo_printf)(ndo,"\n\t        T: %d, R: %d, RES: %d, ISID: %d",(ulong)(*tptr_local >> 7)
                         ,(ulong)(*tptr_local >> 6 & 1),(ulong)(*tptr_local & 0x3f),
                         (ulong)((uint)tptr_local[1] << 0x10 | (uint)tptr_local[2] << 8 |
                                (uint)tptr_local[3]));
      tptr_local = tptr_local + 4;
      len_local = len_local + -4;
    }
  }
LAB_00101c3d:
  (*ndo->ndo_printf)(ndo,"\n\t\t");
  (*ndo->ndo_printf)(ndo,"%s"," [|isis]");
  return 1;
}