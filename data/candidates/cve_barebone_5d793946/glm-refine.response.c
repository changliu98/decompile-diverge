int __cdecl decode_multicast_vpn(netdissect_options *ndo, const u_char *pptr, char *buf, u_int buflen)
{
  const char *route_type_str;
  char *rd_str;
  char *ip_str;
  char *as_str;
  uint32_t as_val;
  u_int offset;
  const u_char *route_data;
  uint8_t addr_length;
  uint8_t route_length;
  uint8_t route_type;

  // Validate minimum packet length for route type and length
  if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || pptr > ndo->ndo_snapend - 2)
    return -2;

  route_type = *pptr;
  route_length = pptr[1];
  route_data = pptr + 2;

  route_type_str = tok2str(&bgp_multicast_vpn_route_type_values, "Unknown", route_type);
  snprintf(buf, buflen, "Route-Type: %s (%u), length: %u", route_type_str, route_type, route_length);

  switch (route_type)
  {
    case 1:
      // Validate 8 bytes for RD
      if (ndo->ndo_snapend - 8 > ndo->ndo_snapend || route_data > ndo->ndo_snapend - 8)
        return -2;
      offset = strlen(buf);
      rd_str = bgp_vpn_rd_print(ndo, route_data);
      ip_str = bgp_vpn_ip_print(ndo, pptr + 10, 8 * ((unsigned int)route_length - 8));
      snprintf(&buf[offset], buflen - offset, ", RD: %s, Originator %s", rd_str, ip_str);
      break;

    case 2:
      // Validate 12 bytes for RD + Source-AS
      if (ndo->ndo_snapend - 12 > ndo->ndo_snapend || route_data > ndo->ndo_snapend - 12)
        return -2;
      offset = strlen(buf);
      rd_str = bgp_vpn_rd_print(ndo, route_data);
      as_val = EXTRACT_32BITS(pptr + 10);
      as_str = as_printf(ndo, astostr, 20, as_val);
      snprintf(&buf[offset], buflen - offset, ", RD: %s, Source-AS %s", rd_str, as_str);
      break;

    case 3:
      // Validate 8 bytes for RD
      if (ndo->ndo_snapend - 8 > ndo->ndo_snapend || route_data > ndo->ndo_snapend - 8)
        return -2;
      offset = strlen(buf);
      rd_str = bgp_vpn_rd_print(ndo, route_data);
      snprintf(&buf[offset], buflen - offset, ", RD: %s", rd_str);

      // Process Source Group and Originator
      const u_char *sg_ptr = pptr + 10;
      addr_length = route_length - bgp_vpn_sg_print(ndo, pptr + 10, buf, buflen);
      
      // Validate addr_length bytes remaining
      if (&ndo->ndo_snapend[-(unsigned __int64)addr_length] > ndo->ndo_snapend || sg_ptr > &ndo->ndo_snapend[-(unsigned __int64)addr_length])
        return -2;
        
      offset = strlen(buf);
      ip_str = bgp_vpn_ip_print(ndo, sg_ptr, 8 * (unsigned int)addr_length);
      snprintf(&buf[offset], buflen - offset, ", Originator %s", ip_str);
      break;

    case 5:
      // Validate 8 bytes for RD
      if (ndo->ndo_snapend - 8 > ndo->ndo_snapend || route_data > ndo->ndo_snapend - 8)
        return -2;
      offset = strlen(buf);
      rd_str = bgp_vpn_rd_print(ndo, route_data);
      snprintf(&buf[offset], buflen - offset, ", RD: %s", rd_str);
      bgp_vpn_sg_print(ndo, pptr + 10, buf, buflen);
      break;

    case 6:
    case 7:
      // Validate 12 bytes for RD + Source-AS
      if (ndo->ndo_snapend - 12 > ndo->ndo_snapend || route_data > ndo->ndo_snapend - 12)
        return -2;
      offset = strlen(buf);
      rd_str = bgp_vpn_rd_print(ndo, route_data);
      as_val = EXTRACT_32BITS(pptr + 10);
      as_str = as_printf(ndo, astostr, 20, as_val);
      snprintf(&buf[offset], buflen - offset, ", RD: %s, Source-AS %s", rd_str, as_str);
      bgp_vpn_sg_print(ndo, pptr + 10, buf, buflen);
      break;

    default:
      return route_length + 2;
  }
  
  return route_length + 2;
}