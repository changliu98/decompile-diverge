void vrrp_print(netdissect_options *ndo,u_char *bp,u_int len,u_char *bp2,int ttl)

{
  byte bVar1;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var2;
  uint16_t uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  uint16_t cksum;
  cksum_vec vec [1];
  char c;
  int i;
  int naddrs;
  uint16_t intvl;
  char *type_s;
  int auth_type;
  int type;
  int version;
  int ttl_local;
  u_char *bp2_local;
  u_int len_local;
  u_char *bp_local;
  netdissect_options *ndo_local;
  
  auth_type = 0;
  if ((ndo->ndo_snapend + -1 <= ndo->ndo_snapend) && (bp <= ndo->ndo_snapend + -1)) {
    uVar4 = (int)(*bp & 0xf0) >> 4;
    bVar1 = *bp;
    pcVar7 = tok2str(type2str,"unknown type (%u)",bVar1 & 0xf);
    (*ndo->ndo_printf)(ndo,"VRRPv%u, %s",(ulong)uVar4,pcVar7);
    if (ttl != 0xff) {
      (*ndo->ndo_printf)(ndo,", (ttl %u)",(ulong)(uint)ttl);
    }
    if (uVar4 < 2) {
      return;
    }
    if (3 < uVar4) {
      return;
    }
    if ((bVar1 & 0xf) != 1) {
      return;
    }
    if ((((ndo->ndo_snapend + -1 <= ndo->ndo_snapend) && (bp + 2 <= ndo->ndo_snapend + -1)) &&
        ((*ndo->ndo_printf)(ndo,", vrid %u, prio %u",(ulong)bp[1],(ulong)bp[2]),
        ndo->ndo_snapend + -1 <= ndo->ndo_snapend)) && (bp + 5 <= ndo->ndo_snapend + -1)) {
      if (uVar4 == 2) {
        auth_type = (int)bp[4];
        p_Var2 = ndo->ndo_printf;
        pcVar7 = tok2str(auth2str,(char *)0x0,auth_type);
        (*p_Var2)(ndo,", authtype %s",pcVar7);
        (*ndo->ndo_printf)(ndo,", intvl %us, length %u",(ulong)bp[5],(ulong)len);
      }
      else {
        (*ndo->ndo_printf)(ndo,", intvl %ucs, length %u",
                           (ulong)(ushort)((bp[4] & 0xf) << 8 | (ushort)bp[5]),(ulong)len);
      }
      if (ndo->ndo_vflag == 0) {
        return;
      }
      uVar5 = (uint)bp[3];
      if (((uVar4 == 2) && (ndo->ndo_snapend + -(ulong)len <= ndo->ndo_snapend)) &&
         ((bp <= ndo->ndo_snapend + -(ulong)len &&
          (vec[0].ptr = bp, vec[0].len = len, uVar3 = in_cksum(vec,1), uVar3 != 0)))) {
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < bp + 6))
        goto LAB_001019e1;
        p_Var2 = ndo->ndo_printf;
        uVar3 = EXTRACT_16BITS(bp + 6);
        (*p_Var2)(ndo,", (bad vrrp cksum %x)",(ulong)uVar3);
      }
      if ((((uVar4 == 3) && (ndo->ndo_snapend + -(ulong)len <= ndo->ndo_snapend)) &&
          (bp <= ndo->ndo_snapend + -(ulong)len)) &&
         (iVar6 = nextproto4_cksum(ndo,(ip *)bp2,bp,len,len,0x70), (short)iVar6 != 0)) {
        p_Var2 = ndo->ndo_printf;
        uVar3 = EXTRACT_16BITS(bp + 6);
        (*p_Var2)(ndo,", (bad vrrp cksum %x)",(ulong)uVar3);
      }
      (*ndo->ndo_printf)(ndo,", addrs");
      if (1 < uVar5) {
        (*ndo->ndo_printf)(ndo,"(%d)",(ulong)uVar5);
      }
      (*ndo->ndo_printf)(ndo,":");
      c = ' ';
      bp_local = bp + 8;
      for (i = 0; i < (int)uVar5; i = i + 1) {
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -1) || (ndo->ndo_snapend + -1 < bp_local + 3))
        goto LAB_001019e1;
        p_Var2 = ndo->ndo_printf;
        pcVar7 = getname(ndo,bp_local);
        (*p_Var2)(ndo,"%c%s",(ulong)(uint)(int)c,pcVar7);
        c = ',';
        bp_local = bp_local + 4;
      }
      if (uVar4 != 2) {
        return;
      }
      if (auth_type != 1) {
        return;
      }
      if ((ndo->ndo_snapend + -1 <= ndo->ndo_snapend) && (bp_local + 7 <= ndo->ndo_snapend + -1)) {
        (*ndo->ndo_printf)(ndo," auth \"");
        iVar6 = fn_printn(ndo,bp_local,8,ndo->ndo_snapend);
        if (iVar6 == 0) {
          (*ndo->ndo_printf)(ndo,"\"");
          return;
        }
        (*ndo->ndo_printf)(ndo,"\"");
      }
    }
  }
LAB_001019e1:
  (*ndo->ndo_printf)(ndo,"[|vrrp]");
  return;
}