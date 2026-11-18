void arp_print(netdissect_options *ndo,u_char *bp,u_int length,u_int caplen)

{
  byte bVar1;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var2;
  uint16_t uVar3;
  uint16_t uVar4;
  uint16_t uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  u_short linkaddr;
  u_short op;
  u_short hrd;
  u_short pro;
  arp_pkthdr *ap;
  u_int caplen_local;
  u_int length_local;
  u_char *bp_local;
  netdissect_options *ndo_local;
  
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < bp)) {
    (*ndo->ndo_printf)(ndo,"%s","[|ARP]");
    return;
  }
  uVar3 = EXTRACT_16BITS(bp);
  uVar4 = EXTRACT_16BITS(bp + 2);
  uVar5 = EXTRACT_16BITS(bp + 6);
  if (uVar3 == 0xf) {
    linkaddr = 1;
  }
  else {
    if (uVar3 == 0x13) {
      atmarp_print(ndo,bp,length,caplen);
      return;
    }
    linkaddr = 0;
  }
  if ((((bp[5] == '\0') && (bp[5] != '\0')) || (ndo->ndo_snapend < ndo->ndo_snapend + -(ulong)bp[5])
      ) || (ndo->ndo_snapend + -(ulong)bp[5] <
            bp + (long)(int)(uint)bp[5] + (long)(int)((uint)bp[4] << 1) + 8)) {
    (*ndo->ndo_printf)(ndo,"%s","[|ARP]");
    (*ndo->ndo_default_print)(ndo,bp,length);
    return;
  }
  if (ndo->ndo_eflag == 0) {
    (*ndo->ndo_printf)(ndo,"ARP, ");
  }
  if (((uVar4 != 0x800) && (uVar4 != 0x1000)) ||
     ((bp[5] != '\x04' || ((bp[4] == '\0' || (ndo->ndo_vflag != 0)))))) {
    p_Var2 = ndo->ndo_printf;
    pcVar7 = tok2str(arphrd_values,"Unknown Hardware (%u)",(uint)uVar3);
    bVar1 = bp[4];
    pcVar8 = tok2str(ethertype_values,"Unknown Protocol (0x%04x)",(uint)uVar4);
    (*p_Var2)(ndo,"%s (len %u), %s (len %u)",pcVar7,(ulong)bVar1,pcVar8,(ulong)bp[5]);
    if (ndo->ndo_vflag == 0) goto LAB_00101e8e;
  }
  p_Var2 = ndo->ndo_printf;
  pcVar7 = "";
  if (ndo->ndo_vflag != 0) {
    pcVar7 = ", ";
  }
  pcVar8 = tok2str(arpop_values,"Unknown (%u)",(uint)uVar5);
  (*p_Var2)(ndo,"%s%s ",pcVar7,pcVar8);
  switch(uVar5) {
  case 1:
    p_Var2 = ndo->ndo_printf;
    pcVar7 = getname(ndo,bp + (long)(int)(uint)bp[5] + (long)(int)((uint)bp[4] << 1) + 8);
    (*p_Var2)(ndo,"who-has %s",pcVar7);
    iVar6 = isnonzero(bp + (long)(int)(uint)bp[5] + (long)(int)(uint)bp[4] + 8,(ulong)bp[4]);
    if (iVar6 != 0) {
      p_Var2 = ndo->ndo_printf;
      pcVar7 = linkaddr_string(ndo,bp + (long)(int)(uint)bp[5] + (long)(int)(uint)bp[4] + 8,
                               (uint)linkaddr,(uint)bp[4]);
      (*p_Var2)(ndo," (%s)",pcVar7);
    }
    p_Var2 = ndo->ndo_printf;
    pcVar7 = getname(ndo,bp + (long)(int)(uint)bp[4] + 8);
    (*p_Var2)(ndo," tell %s",pcVar7);
    break;
  case 2:
    p_Var2 = ndo->ndo_printf;
    pcVar7 = getname(ndo,bp + (long)(int)(uint)bp[4] + 8);
    pcVar8 = linkaddr_string(ndo,bp + 8,(uint)linkaddr,(uint)bp[4]);
    (*p_Var2)(ndo,"%s is-at %s",pcVar7,pcVar8);
    break;
  case 3:
    p_Var2 = ndo->ndo_printf;
    pcVar7 = linkaddr_string(ndo,bp + (long)(int)(uint)bp[5] + (long)(int)(uint)bp[4] + 8,
                             (uint)linkaddr,(uint)bp[4]);
    pcVar8 = linkaddr_string(ndo,bp + 8,(uint)linkaddr,(uint)bp[4]);
    (*p_Var2)(ndo,"who-is %s tell %s",pcVar7,pcVar8);
    break;
  case 4:
    p_Var2 = ndo->ndo_printf;
    pcVar7 = linkaddr_string(ndo,bp + (long)(int)(uint)bp[5] + (long)(int)(uint)bp[4] + 8,
                             (uint)linkaddr,(uint)bp[4]);
    pcVar8 = getname(ndo,bp + (long)(int)(uint)bp[5] + (long)(int)((uint)bp[4] << 1) + 8);
    (*p_Var2)(ndo,"%s at %s",pcVar7,pcVar8);
    break;
  default:
    (*ndo->ndo_default_print)(ndo,bp,caplen);
    return;
  case 8:
    p_Var2 = ndo->ndo_printf;
    pcVar7 = linkaddr_string(ndo,bp + (long)(int)(uint)bp[5] + (long)(int)(uint)bp[4] + 8,
                             (uint)linkaddr,(uint)bp[4]);
    pcVar8 = linkaddr_string(ndo,bp + 8,(uint)linkaddr,(uint)bp[4]);
    (*p_Var2)(ndo,"who-is %s tell %s",pcVar7,pcVar8);
    break;
  case 9:
    p_Var2 = ndo->ndo_printf;
    pcVar7 = linkaddr_string(ndo,bp + 8,(uint)linkaddr,(uint)bp[4]);
    pcVar8 = getname(ndo,bp + (long)(int)(uint)bp[4] + 8);
    (*p_Var2)(ndo,"%s at %s",pcVar7,pcVar8);
  }
LAB_00101e8e:
  (*ndo->ndo_printf)(ndo,", length %u",(ulong)length);
  return;
}