enamemem * lookup_bytestring(netdissect_options *ndo,u_char *bs,uint nlen)

{
  int iVar1;
  u_char *puVar2;
  enamemem *peVar3;
  u_int k;
  u_int j;
  u_int i;
  enamemem *tp;
  uint nlen_local;
  u_char *bs_local;
  netdissect_options *ndo_local;
  
  if (nlen < 6) {
    if (nlen < 4) {
      k = 0;
      j = 0;
    }
    else {
      k = (u_int)CONCAT11(*bs,bs[1]);
      j = (u_int)CONCAT11(bs[2],bs[3]);
    }
    i = 0;
  }
  else {
    k = (u_int)CONCAT11(*bs,bs[1]);
    j = (u_int)CONCAT11(bs[2],bs[3]);
    i = (u_int)CONCAT11(bs[4],bs[5]);
  }
  tp = bytestringtable + ((i ^ j) & 0xfff);
  while( true ) {
    if (tp->e_nxt == (enamemem *)0x0) {
      tp->e_addr0 = (u_short)i;
      tp->e_addr1 = (u_short)j;
      tp->e_addr2 = (u_short)k;
      puVar2 = calloc(1,(ulong)(nlen + 1));
      tp->e_nsap = puVar2;
      if (tp->e_nsap == (u_char *)0x0) {
        (*ndo->ndo_error)(ndo,"lookup_bytestring: calloc");
      }
      memcpy(tp->e_nsap,bs,(ulong)nlen);
      peVar3 = calloc(1,0x20);
      tp->e_nxt = peVar3;
      if (tp->e_nxt == (enamemem *)0x0) {
        (*ndo->ndo_error)(ndo,"lookup_bytestring: calloc");
      }
      return tp;
    }
    if ((((tp->e_addr0 == i) && (tp->e_addr1 == j)) && (tp->e_addr2 == k)) &&
       (iVar1 = memcmp(bs,tp->e_nsap,(ulong)nlen), iVar1 == 0)) break;
    tp = tp->e_nxt;
  }
  return tp;
}