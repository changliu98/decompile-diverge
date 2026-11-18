void eap_print(netdissect_options *ndo, const u_char *p, u_int length) {
  const struct eap *eap;
  const u_char *ep;
  int code, len, type, i;
  eap = (const struct eap *)p;
  if (p + 4 > ndo->ndo_snapend || p > ndo->ndo_snapend - 4) goto trunc;
  if (ndo->ndo_vflag >= 1) {
    ndo->ndo_hexdump(ndo, "%s (%u) v%u, len %u",
                     tok2str(eap_type_values, "unknown", eap->code), eap->code,
                     eap->version, (eap->length << 16));
    ep = p + 4;
    if (eap->code == 0) {
      code = ep[0];
      len = (ep[1] << 8) | ep[2];
      ndo->ndo_hexdump(ndo, ", %s (%u), id %u, len %u",
                       tok2str(eap_code_values, "unknown", code), code, ep[3],
                       len);
      if (p + len > ndo->ndo_snapend || ep > ndo->ndo_snapend - len) goto trunc;
      if (code < 3) {
        type = ep[4];
        ndo->ndo_hexdump(ndo, "\n\t\t Type %s (%u)",
                         tok2str(eap_type_values, "unknown", type), ep[4]);
        switch (type) {
          case 1:
            if (len - 5 > 0) {
              ndo->ndo_hexdump(ndo, ", Identity: ");
              safeputs(ndo, ep + 5, len - 5);
            }
            break;
          case 2:
            if (len - 5 > 0) {
              ndo->ndo_hexdump(ndo, ", Notification: ");
              safeputs(ndo, ep + 5, len - 5);
            }
            break;
          case 3:
            for (i = 5; i < len; i++)
              ndo->ndo_hexdump(ndo, " %s (%u),",
                               tok2str(eap_type_values, "unknown", ep[i]),
                               ep[i]);
            break;
          case 4:
          case 5:
          case 6:
          case 7:
            break;
          case 13:
          case 18:
          case 21:
            ndo->ndo_hexdump(ndo, " flags [%s] 0x%02x,",
                             bittok2str(eap_flags_values, "none", ep[4]), ep[4]);
            if ((ep[4] & 0x80) >> 7)
              ndo->ndo_hexdump(ndo, " len %u",
                               (ep[5] << 24) | (ep[6] << 16) | (ep[7] << 8) |
                                   ep[8]);
            break;
          case 23:
            ndo->ndo_hexdump(ndo, " subtype [%s] 0x%02x,",
                             tok2str(eap_subtype_values, "unknown", ep[4]),
                             ep[4]);
            break;
          case 43:
            ndo->ndo_hexdump(ndo, " FASTv%u", ep[4] & 0x07);
            ndo->ndo_hexdump(ndo, " flags [%s] 0x%02x,",
                             bittok2str(eap_flags_values, "none", ep[4]), ep[4]);
            if ((ep[4] & 0x80) >> 7)
              ndo->ndo_hexdump(ndo, " len %u",
                               (ep[5] << 24) | (ep[6] << 16) | (ep[7] << 8) |
                                   ep[8]);
            break;
        }
      }
    }
  } else {
    ndo->ndo_hexdump(ndo, "%s (%u) v%u, len %u",
                     tok2str(eap_type_values, "unknown", eap->code), eap->code,
                     eap->version, (eap->length));
  }
  return;
trunc:
  ndo->ndo_hexdump(ndo, "\n\t[|EAP]");
}