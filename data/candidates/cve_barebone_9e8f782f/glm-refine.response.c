void __cdecl isoclns_print(netdissect_options *ndo, const uint8_t *p, u_int length, u_int caplen)
{
  const char *nlpid_str;
  const char *separator;
  uint8_t nlpid;

  if (caplen <= 1) {
    ndo->ndo_printf(ndo, "|OSI");
    return;
  }

  if (ndo->ndo_eflag) {
    nlpid_str = tok2str(&nlpid_values, "Unknown", *p);
    ndo->ndo_printf(ndo, "OSI NLPID %s (0x%02x): ", nlpid_str, *p);
  }

  nlpid = *p;
  if (nlpid == 0) {
    separator = ndo->ndo_eflag ? "" : ", ";
    ndo->ndo_printf(ndo, "%slength: %u", separator, length);
    return;
  }

  switch (nlpid) {
    case 8:   // 0x08
      q933_print(ndo, p + 1, length - 1);
      break;
    case 129: // 0x81
      if (!clnp_print(ndo, p, length))
        print_unknown_data(ndo, p, "\n\t", caplen);
      break;
    case 130: // 0x82
      esis_print(ndo, p, length);
      break;
    case 131: // 0x83
      if (!isis_print(ndo, p, length))
        print_unknown_data(ndo, p, "\n\t", caplen);
      break;
    case 142: // 0x8E
      ip6_print(ndo, p + 1, length - 1);
      break;
    case 204: // 0xCC
      ip_print(ndo, p + 1, length - 1);
      break;
    case 207: // 0xCF
      ppp_print(ndo, p + 1, length - 1);
      break;
    default:
      if (!ndo->ndo_eflag)
        ndo->ndo_printf(ndo, "OSI NLPID 0x%02x unknown", *p);
      
      separator = ndo->ndo_eflag ? "" : ", ";
      ndo->ndo_printf(ndo, "%slength: %u", separator, length);
      
      if (caplen > 1)
        print_unknown_data(ndo, p, "\n\t", caplen);
      break;
  }
}