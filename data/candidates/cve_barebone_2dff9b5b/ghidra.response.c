int decode_rt_routing_info(netdissect_options *ndo,u_char *pptr,char *buf,u_int buflen)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint32_t asnum;
  char *pcVar4;
  char *pcVar5;
  u_int plen;
  uint8_t route_target [8];
  u_int buflen_local;
  char *buf_local;
  u_char *pptr_local;
  netdissect_options *ndo_local;
  
  if ((ndo->ndo_snapend + -1 <= ndo->ndo_snapend) && (pptr <= ndo->ndo_snapend + -1)) {
    uVar1 = (uint)*pptr;
    if (uVar1 == 0) {
      snprintf(buf,(ulong)buflen,"default route target");
      return 1;
    }
    if (uVar1 < 0x20) {
      return -1;
    }
    uVar2 = uVar1 - 0x20;
    if (0x40 < uVar2) {
      return -1;
    }
    memset(route_target,0,8);
    if ((((uVar1 - 0x19 >> 3 != 0) || (uVar1 - 0x19 >> 3 == 0)) &&
        (ndo->ndo_snapend + -(ulong)(uVar1 - 0x19 >> 3) <= ndo->ndo_snapend)) &&
       (pptr + 1 <= ndo->ndo_snapend + -(ulong)(uVar1 - 0x19 >> 3))) {
      memcpy(route_target,pptr + 1,(ulong)(uVar1 - 0x19 >> 3));
      if ((uVar2 & 7) != 0) {
        uVar3 = (uVar1 - 0x19 >> 3) - 1;
        route_target[uVar3] = route_target[uVar3] & (byte)(0xff00 >> ((byte)uVar2 & 7));
      }
      asnum = EXTRACT_32BITS(pptr + 1);
      pcVar4 = as_printf(ndo,astostr,0x14,asnum);
      pcVar5 = bgp_vpn_rd_print(ndo,route_target);
      snprintf(buf,(ulong)buflen,"origin AS: %s, route target %s",pcVar4,pcVar5);
      return (uVar1 - 0x19 >> 3) + 5;
    }
  }
  return -2;
}