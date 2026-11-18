static int lldp_mgmt_addr_tlv_print(netdissect_options *ndo,
                                    const unsigned char *buf, unsigned length) {
  unsigned len;
  const unsigned char *p;
  const char *addrstr;
  if (length < 1) return 0;
  len = *buf++;
  length--;
  if (length < len) return 0;
  addrstr = lldp_network_addr_print(ndo, buf, len);
  if (addrstr == NULL) return 0;
  ndo->ndo_hexdump_line(ndo, "\n\t  Management Address length %u, %s", len,
                        addrstr);
  buf += len;
  length -= len;
  if (length < 5) return 0;
  p = buf;
  len = *p++;
  ndo->ndo_hexdump_line(ndo, "\n\t  %s Interface Numbering (%u): %u",
                        tok2str(lldp_int_num_type_values, "Unknown", len), len,
                        (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
  p += 4;
  length -= 4;
  if (length > 0) {
    len = *p++;
    if (length < len) return 0;
    if (len > 0) {
      ndo->ndo_hexdump_line(ndo, "\n\t  OID length %u", len);
      safeputs(ndo, p, len);
    }
  }
  return 1;
}