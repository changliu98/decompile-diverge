int __cdecl isis_print_extd_ip_reach(netdissect_options *ndo, const uint8_t *tptr, const char *ident, uint16_t afi)
{
  const uint8_t *tptr_cur = tptr;
  uint8_t status_byte;
  uint32_t bit_length;
  uint32_t byte_length;
  uint32_t metric;
  uint8_t prefix[16];
  char ident_buffer[20];
  u_int processed;
  u_int sublen;
  uint8_t subtlvtype;
  uint8_t subtlvlen;

  // 1. Read the 4-byte metric
  if (ndo->ndo_snapend - 4 > ndo->ndo_snapend || tptr_cur > ndo->ndo_snapend - 4)
    return 0;
  metric = _byteswap_ulong(*(const uint32_t *)tptr_cur);
  tptr_cur += 4;

  // 2. Parse status byte and bit length based on AFI
  if (afi == 2) // IPv4
  {
    if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || tptr_cur > ndo->ndo_snapend - 1)
      return 0;
    status_byte = *tptr_cur++;
    bit_length = status_byte & 0x3F;
    if (bit_length > 0x20)
    {
      ndo->ndo_printf(ndo, "%sIPv4 prefix: bad bit length %u", ident, bit_length);
      return 0;
    }
    processed = 5;
  }
  else if (afi == 10) // IPv6
  {
    if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || tptr_cur > ndo->ndo_snapend - 1)
      return 0;
    status_byte = *tptr_cur++;
    if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || tptr_cur > ndo->ndo_snapend - 1)
      return 0;
    bit_length = *tptr_cur++;
    if (bit_length > 0x80)
    {
      ndo->ndo_printf(ndo, "%sIPv6 prefix: bad bit length %u", ident, bit_length);
      return 0;
    }
    processed = 6;
  }
  else
  {
    return 0;
  }

  // 3. Parse the prefix bytes
  byte_length = (bit_length + 7) >> 3;
  if (ndo->ndo_snapend - byte_length > ndo->ndo_snapend || tptr_cur > ndo->ndo_snapend - byte_length)
    return 0;

  memset(prefix, 0, sizeof(prefix));
  memcpy(prefix, tptr_cur, byte_length);
  tptr_cur += byte_length;
  processed += byte_length;

  // 4. Print the prefix
  if (afi == 2)
  {
    const char *ip_str = ipaddr_string(ndo, prefix);
    ndo->ndo_printf(ndo, "%sIPv4 prefix: %15s/%u", ident, ip_str, bit_length);
  }
  else // afi == 10
  {
    const char *ip6_str = ip6addr_string(ndo, prefix);
    ndo->ndo_printf(ndo, "%sIPv6 prefix: %s/%u", ident, ip6_str, bit_length);
  }

  // 5. Print status and metric
  const char *dist_str = (status_byte & 0x80) ? "down" : "up";
  ndo->ndo_printf(ndo, ", Distribution: %s, Metric: %u", dist_str, metric);

  // 6. Print flags
  if (afi == 2)
  {
    if (status_byte & 0x40)
      ndo->ndo_printf(ndo, ", sub-TLVs present");
  }
  else // afi == 10
  {
    const char *ext_str = (status_byte & 0x40) ? "External" : "Internal";
    const char *subtlv_str = (status_byte & 0x20) ? ", sub-TLVs present" : "";
    ndo->ndo_printf(ndo, ", %s%s", ext_str, subtlv_str);
  }

  // 7. Parse and print sub-TLVs if present
  if ((afi == 2 && (status_byte & 0x40)) || (afi == 10 && (status_byte & 0x20)))
  {
    if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || tptr_cur > ndo->ndo_snapend - 1)
      return 0;
    sublen = *tptr_cur++;
    processed += sublen + 1;
    ndo->ndo_printf(ndo, " (%u)", sublen);

    while (sublen)
    {
      if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || tptr_cur > ndo->ndo_snapend - 2)
        return 0;
      subtlvtype = *tptr_cur++;
      subtlvlen = *tptr_cur++;
      snprintf(ident_buffer, sizeof(ident_buffer), "%s  ", ident);
      
      if (!isis_print_ip_reach_subtlv(ndo, tptr_cur, subtlvtype, subtlvlen, ident_buffer))
        return 0;
      
      tptr_cur += subtlvlen;
      sublen -= subtlvlen + 2;
    }
  }

  return processed;
}