int xid_map_enter(netdissect_options *ndo,sunrpc_msg *rp,u_char *bp)

{
  ip *piVar1;
  uint32_t uVar2;
  long lVar3;
  xid_map_entry *xmep;
  ip6_hdr *ip6;
  ip *ip;
  u_char *bp_local;
  sunrpc_msg *rp_local;
  netdissect_options *ndo_local;
  int local_c;
  
  ip = (ip *)0x0;
  ip6 = (ip6_hdr *)0x0;
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -4) ||
     (ndo->ndo_snapend + -4 < (u_char *)((long)&rp->ru + 8U))) {
    local_c = 0;
  }
  else {
    piVar1 = (ip *)bp;
    if ((*bp >> 4 == 4) || (ip6 = (ip6_hdr *)bp, piVar1 = ip, *bp >> 4 == 6)) {
      ip = piVar1;
      lVar3 = (long)xid_map_next;
      xid_map_next = xid_map_next + 1;
      if (0x3f < xid_map_next) {
        xid_map_next = 0;
      }
      xid_map[lVar3].xid = rp->rm_xid;
      if (ip == (ip *)0x0) {
        if (ip6 != (ip6_hdr *)0x0) {
          xid_map[lVar3].ipver = 6;
          *(undefined8 *)&xid_map[lVar3].client.__in6_u = *(undefined8 *)&(ip6->ip6_src).__in6_u;
          *(undefined8 *)((long)&xid_map[lVar3].client.__in6_u + 8) =
               *(undefined8 *)((long)&(ip6->ip6_src).__in6_u + 8);
          *(undefined8 *)&xid_map[lVar3].server.__in6_u = *(undefined8 *)&(ip6->ip6_dst).__in6_u;
          *(undefined8 *)((long)&xid_map[lVar3].server.__in6_u + 8) =
               *(undefined8 *)((long)&(ip6->ip6_dst).__in6_u + 8);
        }
      }
      else {
        xid_map[lVar3].ipver = 4;
        xid_map[lVar3].client.__in6_u.__u6_addr32[0] = *(uint32_t *)(ip->ip_src).bytes;
        xid_map[lVar3].server.__in6_u.__u6_addr32[0] = *(uint32_t *)(ip->ip_dst).bytes;
      }
      uVar2 = EXTRACT_32BITS((void *)((long)&rp->ru + 0xc));
      xid_map[lVar3].proc = uVar2;
      uVar2 = EXTRACT_32BITS((void *)((long)&rp->ru + 8));
      xid_map[lVar3].vers = uVar2;
      local_c = 1;
    }
    else {
      local_c = 1;
    }
  }
  return local_c;
}