int __cdecl xid_map_enter(netdissect_options *ndo, const sunrpc_msg *rp, const u_char *bp_0)
{
  int v4; // [rsp+4h] [rbp-3Ch]
  xid_map_entry *xmep; // [rsp+8h] [rbp-38h]
  const ip6_hdr *ip6; // [rsp+10h] [rbp-30h]
  const ip *ip_0; // [rsp+18h] [rbp-28h]

  ip_0 = 0LL;
  ip6 = 0LL;
  if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || (const u_char *)&rp->ru.RM_rmb.rp_reject.ru > ndo->ndo_snapend - 4 )
    return 0;
  v4 = *bp_0 >> 4;
  if ( v4 == 4 )
  {
    ip_0 = (const ip *)bp_0;
  }
  else
  {
    if ( v4 != 6 )
      return 1;
    ip6 = (const ip6_hdr *)bp_0;
  }
  xmep = (xid_map_entry *)&xid_map[12 * xid_map_next++];
  if ( xid_map_next >= 64 )
    xid_map_next = 0;
  xmep->xid = rp->rm_xid;
  if ( ip_0 )
  {
    xmep->ipver = 4;
    xmep->client.__in6_u.__u6_addr32[0] = (uint32_t)ip_0->ip_src;
    xmep->server.__in6_u.__u6_addr32[0] = (uint32_t)ip_0->ip_dst;
  }
  else if ( ip6 )
  {
    xmep->ipver = 6;
    *(_QWORD *)xmep->client.__in6_u.__u6_addr8 = *(_QWORD *)ip6->ip6_src.__in6_u.__u6_addr8;
    *(_QWORD *)&xmep->client.__in6_u.__u6_addr32[2] = *(_QWORD *)&ip6->ip6_src.__in6_u.__u6_addr32[2];
    *(_QWORD *)xmep->server.__in6_u.__u6_addr8 = *(_QWORD *)ip6->ip6_dst.__in6_u.__u6_addr8;
    *(_QWORD *)&xmep->server.__in6_u.__u6_addr32[2] = *(_QWORD *)&ip6->ip6_dst.__in6_u.__u6_addr32[2];
  }
  xmep->proc = EXTRACT_32BITS((char *)&rp->ru.RM_rmb.rp_reject.ru + 4);
  xmep->vers = EXTRACT_32BITS(&rp->ru.RM_rmb.rp_reject.ru);
  return 1;
}