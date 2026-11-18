int __cdecl decode_multicast_vpn(netdissect_options *ndo, const u_char *pptr, char *buf, u_int buflen)
{
  const char *v4; // rax
  char *v5; // rax
  uint32_t v6; // eax
  char *v7; // rax
  char *v8; // rax
  char *v9; // rax
  char *v10; // rax
  uint32_t v11; // eax
  char *v12; // rax
  char *v14; // [rsp+18h] [rbp-B8h]
  char *v15; // [rsp+68h] [rbp-68h]
  char *v16; // [rsp+80h] [rbp-50h]
  u_int offset; // [rsp+A4h] [rbp-2Ch]
  u_int offseta; // [rsp+A4h] [rbp-2Ch]
  u_int offsetb; // [rsp+A4h] [rbp-2Ch]
  u_int offsetc; // [rsp+A4h] [rbp-2Ch]
  u_int offsetd; // [rsp+A4h] [rbp-2Ch]
  u_int offsete; // [rsp+A4h] [rbp-2Ch]
  uint8_t addr_length; // [rsp+A9h] [rbp-27h]
  uint8_t route_length; // [rsp+AAh] [rbp-26h]
  uint8_t route_type; // [rsp+ABh] [rbp-25h]
  const u_char *pptra; // [rsp+B8h] [rbp-18h]
  const u_char *pptrb; // [rsp+B8h] [rbp-18h]

  if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend || pptr > ndo->ndo_snapend - 2 )
    return -2;
  route_type = *pptr;
  pptra = pptr + 2;
  route_length = pptr[1];
  v4 = tok2str(&bgp_multicast_vpn_route_type_values, "Unknown", *pptr);
  snprintf(buf, buflen, "Route-Type: %s (%u), length: %u", v4, route_type, route_length);
  switch ( route_type )
  {
    case 1u:
      if ( ndo->ndo_snapend - 8 > ndo->ndo_snapend || pptra > ndo->ndo_snapend - 8 )
        return -2;
      offset = strlen(buf);
      v16 = bgp_vpn_rd_print(ndo, pptra);
      v5 = bgp_vpn_ip_print(ndo, pptr + 10, 8 * ((unsigned int)route_length - 8));
      snprintf(&buf[offset], buflen - offset, ", RD: %s, Originator %s", v16, v5);
      break;
    case 2u:
      if ( ndo->ndo_snapend - 12 > ndo->ndo_snapend || pptra > ndo->ndo_snapend - 12 )
        return -2;
      offseta = strlen(buf);
      v15 = bgp_vpn_rd_print(ndo, pptra);
      v6 = EXTRACT_32BITS(pptr + 10);
      v7 = as_printf(ndo, astostr, 20, v6);
      snprintf(&buf[offseta], buflen - offseta, ", RD: %s, Source-AS %s", v15, v7);
      break;
    case 3u:
      if ( ndo->ndo_snapend - 8 > ndo->ndo_snapend )
        return -2;
      if ( pptra > ndo->ndo_snapend - 8 )
        return -2;
      offsetb = strlen(buf);
      v8 = bgp_vpn_rd_print(ndo, pptra);
      snprintf(&buf[offsetb], buflen - offsetb, ", RD: %s", v8);
      pptrb = pptr + 10;
      addr_length = route_length - bgp_vpn_sg_print(ndo, pptr + 10, buf, buflen);
      if ( &ndo->ndo_snapend[-(unsigned __int64)addr_length] > ndo->ndo_snapend
        || pptrb > &ndo->ndo_snapend[-(unsigned __int64)addr_length] )
      {
        return -2;
      }
      offsetc = strlen(buf);
      v9 = bgp_vpn_ip_print(ndo, pptrb, 8 * (unsigned int)addr_length);
      snprintf(&buf[offsetc], buflen - offsetc, ", Originator %s", v9);
      break;
    case 5u:
      if ( ndo->ndo_snapend - 8 > ndo->ndo_snapend || pptra > ndo->ndo_snapend - 8 )
        return -2;
      offsetd = strlen(buf);
      v10 = bgp_vpn_rd_print(ndo, pptra);
      snprintf(&buf[offsetd], buflen - offsetd, ", RD: %s", v10);
      bgp_vpn_sg_print(ndo, pptr + 10, buf, buflen);
      break;
    case 6u:
    case 7u:
      if ( ndo->ndo_snapend - 8 > ndo->ndo_snapend || pptra > ndo->ndo_snapend - 8 )
        return -2;
      offsete = strlen(buf);
      v14 = bgp_vpn_rd_print(ndo, pptra);
      v11 = EXTRACT_32BITS(pptr + 10);
      v12 = as_printf(ndo, astostr, 20, v11);
      snprintf(&buf[offsete], buflen - offsete, ", RD: %s, Source-AS %s", v14, v12);
      bgp_vpn_sg_print(ndo, pptr + 10, buf, buflen);
      break;
    default:
      return route_length + 2;
  }
  return route_length + 2;
}