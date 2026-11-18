void __cdecl handle_ppp(netdissect_options *ndo, u_int proto, const u_char *p, int length)
{
  const char *type_str;
  int (*ndo_printf)(netdissect_options *, const char *, ...);

  // Check for PPP HDLC frames (0xFF00 mask corresponds to 0xFFxx)
  if ((proto & 0xFF00) == 0xFF00)
  {
    ppp_hdlc(ndo, p - 1, length);
    return;
  }

  switch (proto)
  {
    case 0x0021:
    case 0x002F:
    case 0x0800:
      ip_print(ndo, p, length);
      return;

    case 0x0023:
      isoclns_print(ndo, p, length, length);
      return;

    case 0x002B:
    case 0x8137:
      ipx_print(ndo, p, length);
      return;

    case 0x003D:
      handle_mlppp(ndo, p, length);
      return;

    case 0x0057:
    case 0x86DD:
      ip6_print(ndo, p, length);
      return;

    case 0x00FD:
      ndo->ndo_printf(ndo, "compressed PPP data");
      return;

    case 0x0281:
    case 0x0283:
      mpls_print(ndo, p, length);
      return;

    case 0x8021:
    case 0x8023:
    case 0x8057:
    case 0x80FD:
    case 0x8281:
    case 0xC021:
    case 0xC02B:
      handle_ctrl_proto(ndo, proto, p, length);
      return;

    case 0xC023:
      handle_pap(ndo, p, length);
      return;

    case 0xC02D:
      handle_bap(ndo, p, length);
      break;

    case 0xC223:
      handle_chap(ndo, p, length);
      break;

    default:
      ndo_printf = ndo->ndo_printf;
      type_str = tok2str(&ppptype2str, "unknown PPP protocol (0x%04x)", proto);
      ndo_printf(ndo, "%s ", type_str);
      print_unknown_data(ndo, p, "\n\t", length);
      break;
  }
}