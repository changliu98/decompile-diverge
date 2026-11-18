int __cdecl rpki_rtr_pdu_print(netdissect_options *ndo, const u_char *tptr, u_int indent)
{
  const u_char *tptr_curr;
  u_int pdu_type;
  u_int pdu_len;
  u_int hexdump;
  u_int version;
  const char *pdu_name;
  u_int encapsulated_pdu_length;
  u_int error_code;
  u_int tlen;
  u_int text_length;
  const char *error_name;

  tptr_curr = tptr;
  version = tptr[0];
  pdu_type = tptr[1];
  pdu_len = ntohl(*(u_int *)(tptr + 4));

  // Check if the packet length is valid and within bounds
  if (ndo->ndo_snapend - pdu_len > ndo->ndo_snapend || tptr > ndo->ndo_snapend - pdu_len)
    return 1;

  hexdump = 0;
  pdu_name = tok2str(&rpki_rtr_pdu_values, "Unknown", pdu_type);
  ndo->ndo_printf(ndo, "%sRPKI-RTRv%u, %s PDU (%u), length: %u", indent_string(8), version, pdu_name, pdu_type, pdu_len);

  switch (pdu_type)
  {
    case 0:
    case 1:
    case 7:
      ndo->ndo_printf(
        ndo,
        "%sSession ID: 0x%04x, Serial: %u",
        indent_string(indent + 2),
        ntohs(*(u_short *)(tptr + 2)),
        ntohl(*(u_int *)(tptr + 8)));
      break;
    case 2:
    case 8:
      break;
    case 3:
      ndo->ndo_printf(
        ndo,
        "%sSession ID: 0x%04x",
        indent_string(indent + 2),
        ntohs(*(u_short *)(tptr + 2)));
      break;
    case 4:
      ndo->ndo_printf(
        ndo,
        "%sIPv4 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
        indent_string(indent + 2),
        getname(ndo, tptr + 12),
        tptr[9],
        tptr[10],
        ntohl(*(u_int *)(tptr + 16)),
        tptr[8]);
      break;
    case 6:
      ndo->ndo_printf(
        ndo,
        "%sIPv6 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
        indent_string(indent + 2),
        getname6(ndo, tptr + 12),
        tptr[9],
        tptr[10],
        ntohl(*(u_int *)(tptr + 28)),
        tptr[8]);
      break;
    case 0xA:
      encapsulated_pdu_length = ntohl(*(u_int *)(tptr + 8));
      if (ndo->ndo_snapend - encapsulated_pdu_length > ndo->ndo_snapend)
        return 1;
      if (tptr > ndo->ndo_snapend - encapsulated_pdu_length)
        return 1;

      error_code = ntohs(*(u_short *)(tptr + 2));
      error_name = tok2str(&rpki_rtr_error_codes, "Unknown", error_code);
      ndo->ndo_printf(
        ndo,
        "%sError code: %s (%u), Encapsulated PDU length: %u",
        indent_string(indent + 2),
        error_name,
        error_code,
        encapsulated_pdu_length);

      tptr_curr = tptr + 12;
      tlen = pdu_len - 12;

      if (encapsulated_pdu_length && encapsulated_pdu_length <= tlen)
      {
        ndo->ndo_printf(ndo, "%s-----encapsulated PDU-----", indent_string(indent + 4));
        if (rpki_rtr_pdu_print(ndo, tptr_curr, indent + 2))
          return 1;
      }

      tptr_curr += encapsulated_pdu_length;
      tlen -= encapsulated_pdu_length;
      text_length = 0;

      if (tlen > 4)
      {
        text_length = ntohl(*(u_int *)tptr_curr);
        tptr_curr += 4;
        tlen -= 4;
      }

      if (ndo->ndo_snapend - text_length > ndo->ndo_snapend)
        return 1;
      if (tptr_curr > ndo->ndo_snapend - text_length)
        return 1;

      if (text_length && text_length <= tlen)
      {
        ndo->ndo_printf(ndo, "%sError text: ", indent_string(indent + 2));
        if (fn_printn(ndo, tptr_curr, text_length, ndo->ndo_snapend))
          return 1;
      }
      break;
    default:
      hexdump = 1;
      break;
  }

  if (ndo->ndo_vflag > 1 || (ndo->ndo_vflag && hexdump))
    print_unknown_data(ndo, tptr_curr, "\n\t  ", pdu_len);

  return 0;
}