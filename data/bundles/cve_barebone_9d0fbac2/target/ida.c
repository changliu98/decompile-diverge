void __cdecl handle_ppp(netdissect_options *ndo, u_int proto, const u_char *p, int length)
{
  const char *v4; // rax
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+8h] [rbp-28h]

  if ( (proto & 0xFF00) == 32256 )
  {
    ppp_hdlc(ndo, p - 1, length);
    return;
  }
  switch ( proto )
  {
    case 0x21u:
      goto LABEL_31;
    case 0x23u:
      isoclns_print(ndo, p, length, length);
      return;
    case 0x2Bu:
      goto LABEL_33;
    case 0x2Fu:
      goto LABEL_31;
    case 0x3Du:
      handle_mlppp(ndo, p, length);
      return;
    case 0x57u:
      goto LABEL_32;
    case 0xFDu:
      ndo->ndo_printf(ndo, "compressed PPP data");
      return;
    case 0x281u:
    case 0x283u:
      mpls_print(ndo, p, length);
      return;
    case 0x800u:
LABEL_31:
      ip_print(ndo, p, length);
      return;
    case 0x8021u:
    case 0x8023u:
    case 0x8057u:
    case 0x80FDu:
      goto LABEL_26;
    case 0x8137u:
LABEL_33:
      ipx_print(ndo, p, length);
      return;
    case 0x8281u:
      goto LABEL_26;
    case 0x86DDu:
LABEL_32:
      ip6_print(ndo, p, length);
      return;
    case 0xC021u:
      goto LABEL_26;
    case 0xC023u:
      handle_pap(ndo, p, length);
      return;
    case 0xC02Bu:
LABEL_26:
      handle_ctrl_proto(ndo, proto, p, length);
      return;
    case 0xC02Du:
      handle_bap(ndo, p, length);
      break;
    case 0xC223u:
      handle_chap(ndo, p, length);
      break;
    default:
      ndo_printf = ndo->ndo_printf;
      v4 = tok2str(&ppptype2str, "unknown PPP protocol (0x%04x)", proto);
      ndo_printf(ndo, "%s ", v4);
      print_unknown_data(ndo, p, "\n\t", length);
      break;
  }
}