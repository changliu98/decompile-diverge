void isoclns_print(struct vty *vty, const u_char *p, u_int len, u_int caplen) {
  if (caplen < 2) {
    vty->print(vty, "|OSI");
    return;
  }
  if (vty->detail)
    vty->print(vty, "OSI NLPID %s (0x%02x): ",
               tok2str(nlp_values, "Unknown", *p), *p);
  switch (*p) {
    case 0x00:
      vty->print(vty, "%slength: %u", vty->detail ? "" : ", ", len);
      break;
    case 0x80:
      if (clnp_print(vty, p, len) == 0)
        print_unknown_data(vty, p, "\n\t", caplen);
      break;
    case 0x82:
      if (isis_print(vty, p, len) == 0)
        print_unknown_data(vty, p, "\n\t", caplen);
      break;
    case 0x81:
      esis_print(vty, p, len);
      break;
    case 0xcc:
      ip_print(vty, p + 1, len - 1);
      break;
    case 0xce:
      ip6_print(vty, p + 1, len - 1);
      break;
    case 0xcf:
      ppp_print(vty, p + 1, len - 1);
      break;
    case 0x08:
      q933_print(vty, p + 1, len - 1);
      break;
    default:
      if (!vty->detail) vty->print(vty, "OSI NLPID 0x%02x unknown", *p);
      vty->print(vty, "%slength: %u", vty->detail ? "" : ", ", len);
      if (caplen > 1) print_unknown_data(vty, p, "\n\t", caplen);
      break;
  }
}