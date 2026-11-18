void ripng_print(netdissect_options *ndo,u_char *dat,uint length)

{
  ulong uVar1;
  uint uVar2;
  ulong uVar3;
  bool bVar4;
  uint local_50;
  in6_addr *__a;
  int trunc;
  int j;
  u_int i;
  u_int amt;
  netinfo6 *ni;
  rip6 *rp;
  uint length_local;
  u_char *dat_local;
  netdissect_options *ndo_local;
  
  if (ndo->ndo_snapend < dat) {
    return;
  }
  uVar2 = (int)ndo->ndo_snapend - (int)dat;
  local_50 = length;
  if (uVar2 < length) {
    local_50 = uVar2;
  }
  if (local_50 < 4) {
    return;
  }
  i = local_50 - 4;
  if (*dat == '\x01') {
    uVar2 = SUB164(ZEXT416(length) / ZEXT816(0x14),0);
    if ((uVar2 == 1) && (dat[0x17] == '\x10')) {
      bVar4 = false;
      if ((*(int *)(dat + 4) == 0) &&
         ((bVar4 = false, *(int *)(dat + 8) == 0 && (bVar4 = false, *(int *)(dat + 0xc) == 0)))) {
        bVar4 = *(int *)(dat + 0x10) == 0;
      }
      if (bVar4) {
        (*ndo->ndo_printf)(ndo," ripng-req dump",(ulong)length % 0x14);
        goto LAB_00101592;
      }
    }
    if ((long)(int)uVar2 * 0x14 - (ulong)(length - 4) == 0) {
      (*ndo->ndo_printf)(ndo," ripng-req %d:",(ulong)uVar2);
    }
    else {
      (*ndo->ndo_printf)(ndo," ripng-req %d[%u]:",(ulong)uVar2,(ulong)length);
    }
    ni = (netinfo6 *)(dat + 4);
    for (; 0x13 < i; i = i - 0x14) {
      if (ndo->ndo_vflag < 2) {
        (*ndo->ndo_printf)(ndo," ");
      }
      else {
        (*ndo->ndo_printf)(ndo,"\n\t");
      }
      rip6_entry_print(ndo,ni,0);
      ni = ni + 1;
    }
  }
  else if (*dat == '\x02') {
    uVar2 = SUB164(ZEXT416(length) / ZEXT816(0x14),0);
    if ((long)(int)uVar2 * 0x14 - (ulong)(length - 4) == 0) {
      (*ndo->ndo_printf)(ndo," ripng-resp %d:",(ulong)uVar2);
    }
    else {
      (*ndo->ndo_printf)(ndo," ripng-resp %d[%u]:",(ulong)uVar2,(ulong)length);
    }
    uVar1 = (ulong)i;
    uVar3 = (ulong)i;
    ni = (netinfo6 *)(dat + 4);
    for (; 0x13 < i; i = i - 0x14) {
      if (ndo->ndo_vflag < 2) {
        (*ndo->ndo_printf)(ndo," ");
      }
      else {
        (*ndo->ndo_printf)(ndo,"\n\t");
      }
      rip6_entry_print(ndo,ni,(uint)ni->rip6_metric);
      ni = ni + 1;
    }
    if ((uVar1 / 0x14) * 0x14 - uVar3 != 0) {
      (*ndo->ndo_printf)(ndo,"[|ripng]");
    }
  }
  else {
    (*ndo->ndo_printf)(ndo," ripng-%d ?? %u",(ulong)*dat,(ulong)length);
  }
LAB_00101592:
  if (dat[1] != '\x01') {
    (*ndo->ndo_printf)(ndo," [vers %d]",(ulong)dat[1]);
  }
  return;
}