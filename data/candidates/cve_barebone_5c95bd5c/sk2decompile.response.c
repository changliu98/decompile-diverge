int rpki_rtr_pdu_print(netdissect_options *ndo, const unsigned char *pdu,
                       unsigned indent) {
  unsigned pdu_type = pdu[1];
  unsigned pdu_len = (pdu[2] << 24) | (pdu[3] << 16) | (pdu[4] << 8) | pdu[5];
  if (pdu + pdu_len > ndo->ndo_snapend || pdu > ndo->ndo_snapend - pdu_len)
    return 1;
  int unknown = 0;
  ndo->ndo_hexdump_line(ndo, "%sRPKI-RTRv%u, %s PDU (%u), length: %u",
                        indent_string(8), pdu[0],
                        tok2str(rpki_rtr_pdu_type_values, "Unknown", pdu_type),
                        pdu_type, pdu_len);
  switch (pdu_type) {
    case 0:
    case 1:
    case 7:
      ndo->ndo_hexdump_line(ndo, "%sSession ID: 0x%04x, Serial: %u",
                            indent_string(indent + 2), (pdu[2] << 8) | pdu[3],
                            (pdu[4] << 24) | (pdu[5] << 16) | (pdu[6] << 8) | pdu[7]);
      break;
    case 2:
    case 8:
      break;
    case 3:
      ndo->ndo_hexdump_line(ndo, "%sSession ID: 0x%04x",
                            indent_string(indent + 2), (pdu[2] << 8) | pdu[3]);
      break;
    case 4:
      ndo->ndo_hexdump_line(ndo, "%sIPv4 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
                            indent_string(indent + 2), getname(ndo, pdu + 12),
                            pdu[9], pdu[10],
                            (pdu[11] << 24) | (pdu[12] << 16) | (pdu[13] << 8) | pdu[14],
                            pdu[8]);
      break;
    case 6:
      ndo->ndo_hexdump_line(ndo, "%sIPv6 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
                            indent_string(indent + 2), getname6(ndo, pdu + 12),
                            pdu[9], pdu[10],
                            (pdu[11] << 24) | (pdu[12] << 16) | (pdu[13] << 8) | pdu[14],
                            pdu[8]);
      break;
    case 10: {
      unsigned encap_len =
          (pdu[4] << 24) | (pdu[5] << 16) | (pdu[6] << 8) | pdu[7];
      if (pdu + encap_len > ndo->ndo_snapend || pdu > ndo->ndo_snapend - encap_len)
        return 1;
      unsigned error_code = (pdu[2] << 8) | pdu[3];
      ndo->ndo_hexdump_line(ndo, "%sError code: %s (%u), Encapsulated PDU length: %u",
                            indent_string(indent + 2),
                            tok2str(rpki_rtr_error_code_values, "Unknown",
                                    error_code),
                            error_code, encap_len);
      pdu += 12;
      pdu_len -= 12;
      if (encap_len && encap_len <= pdu_len) {
        ndo->ndo_hexdump_line(ndo, "%s-----encapsulated PDU-----",
                              indent_string(indent + 4));
        if (rpki_rtr_pdu_print(ndo, pdu, indent + 2)) return 1;
      }
      pdu += encap_len;
      pdu_len -= encap_len;
      unsigned error_len = 0;
      if (pdu_len >= 4) {
        error_len = (pdu[0] << 24) | (pdu[1] << 16) | (pdu[2] << 8) | pdu[3];
        pdu += 4;
        pdu_len -= 4;
      }
      if (pdu + error_len > ndo->ndo_snapend || pdu > ndo->ndo_snapend - error_len)
        return 1;
      if (error_len && error_len <= pdu_len) {
        ndo->ndo_hexdump_line(ndo, "%sError text: ", indent_string(indent + 2));
        if (fn_printn(ndo, pdu, error_len, ndo->ndo_snapend)) return 1;
      }
      break;
    }
    default:
      unknown = 1;
      break;
  }
  if (ndo->ndo_vflag > 1 || (ndo->ndo_vflag && unknown))
    print_unknown_data(ndo, pdu, "\n\t  ", pdu_len);
  return 0;
}