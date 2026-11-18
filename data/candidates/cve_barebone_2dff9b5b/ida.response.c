int __cdecl decode_rt_routing_info(netdissect_options *ndo, const u_char *pptr, char *buf, u_int buflen)
{
  u_int v4; // eax
  char *v5; // rax
  netdissect_options *v7; // [rsp+0h] [rbp-50h]
  char *s; // [rsp+8h] [rbp-48h]
  size_t maxlen; // [rsp+10h] [rbp-40h]
  char *v10; // [rsp+18h] [rbp-38h]
  u_int plen; // [rsp+20h] [rbp-30h]
  u_int plena; // [rsp+20h] [rbp-30h]
  uint8_t route_target[8]; // [rsp+24h] [rbp-2Ch] BYREF
  u_int buflena; // [rsp+2Ch] [rbp-24h]
  char *bufa; // [rsp+30h] [rbp-20h]
  const u_char *pptra; // [rsp+38h] [rbp-18h]
  netdissect_options *ndoa; // [rsp+40h] [rbp-10h]

  ndoa = ndo;
  pptra = pptr;
  bufa = buf;
  buflena = buflen;
  if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend || pptra > ndoa->ndo_snapend - 1 )
    return -2;
  plen = *pptra;
  if ( *pptra )
  {
    if ( plen >= 0x20 )
    {
      plena = plen - 32;
      if ( plena <= 0x40 )
      {
        memset(route_target, 0, sizeof(route_target));
        if ( &ndoa->ndo_snapend[-(unsigned __int64)((plena + 7) >> 3)] > ndoa->ndo_snapend
          || pptra + 1 > &ndoa->ndo_snapend[-(unsigned __int64)((plena + 7) >> 3)] )
        {
          return -2;
        }
        memcpy(route_target, pptra + 1, (plena + 7) >> 3);
        if ( (plena & 7) != 0 )
          route_target[((plena + 7) >> 3) - 1] &= 65280 >> (plena & 7);
        s = bufa;
        maxlen = buflena;
        v7 = ndoa;
        v4 = EXTRACT_32BITS(pptra + 1);
        v10 = as_printf(v7, astostr, 20, v4);
        v5 = bgp_vpn_rd_print(ndoa, route_target);
        snprintf(s, maxlen, "origin AS: %s, route target %s", v10, v5);
        return ((plena + 7) >> 3) + 5;
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
  else
  {
    snprintf(bufa, buflena, "default route target");
    return 1;
  }
}