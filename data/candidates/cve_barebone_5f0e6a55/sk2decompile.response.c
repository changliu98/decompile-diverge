u_int ieee802_15_4_if_print(netdissect_options *ndo,
                            const struct ieee802154_hdr *fh, const u_int *pd) {
  const struct ieee802154_hdr_framever *fhfv;
  const u_int *cp;
  u_int length;
  u_int fcf;
  u_int seq;
  u_int panid;
  u_int short_addr;
  u_int dst_addr;
  fhfv = (const struct ieee802154_hdr_framever *)pd;
  cp = pd + sizeof(*fhfv);
  length = fh->fh_length;
  short_addr = 0;
  if (length < sizeof(*fhfv)) goto trunc;
  fcf = fhfv->fcf;
  seq = fhfv->seq;
  panid = fhfv->panid;
  length -= sizeof(*fhfv);
  ndo->ndo_vflag(ndo, "IEEE 802.15.4 %s packet ",
                 ieee802_15_4_frame_type[fcf & 0x07]);
  if (ndo->ndo_vflag_ac) ndo->ndo_vflag(ndo, "seq %02x ", seq);
  switch ((fcf >> 10) & 0x03) {
    case 0:
      if (fcf & 0x40) goto trunc;
      if (ndo->ndo_vflag_ac) ndo->ndo_vflag(ndo, "none ");
      break;
    case 1:
      if (ndo->ndo_vflag_ac)
        ndo->ndo_vflag(ndo, "reserved destination addressing mode");
      return (3);
    case 2:
      if (length < 2) goto trunc;
      short_addr = (cp[0] << 8) | cp[1];
      cp += 2;
      length -= 2;
      fcf += 2;
      if (length < 2) goto trunc;
      if (ndo->ndo_vflag_ac)
        ndo->ndo_vflag(ndo, "%04x:%04x ", short_addr, (cp[0] << 8) | cp[1]);
      cp += 2;
      length -= 2;
      fcf += 2;
      break;
    case 3:
      if (length < 2) goto trunc;
      short_addr = (cp[0] << 8) | cp[1];
      cp += 2;
      length -= 2;
      fcf += 2;
      if (length < 8) goto trunc;
      if (ndo->ndo_vflag_ac)
        ndo->ndo_vflag(ndo, "%04x:%s ", short_addr, le64addr_string(ndo, cp));
      cp += 8;
      length -= 8;
      fcf += 8;
      break;
  }
  if (ndo->ndo_vflag_ac) ndo->ndo_vflag(ndo, "< ");
  switch ((fcf >> 14) & 0x03) {
    case 0:
      if (ndo->ndo_vflag_ac) ndo->ndo_vflag(ndo, "none ");
      break;
    case 1:
      if (ndo->ndo_vflag_ac)
        ndo->ndo_vflag(ndo, "reserved source addressing mode");
      return (0);
    case 2:
      if (fcf & 0x40) goto trunc;
      if (length < 2) goto trunc;
      short_addr = (cp[0] << 8) | cp[1];
      cp += 2;
      length -= 2;
      fcf += 2;
      if (length < 2) goto trunc;
      if (ndo->ndo_vflag_ac)
        ndo->ndo_vflag(ndo, "%04x:%04x ", short_addr, (cp[0] << 8) | cp[1]);
      cp += 2;
      length -= 2;
      fcf += 2;
      break;
    case 3:
      if (fcf & 0x40) goto trunc;
      if (length < 2) goto trunc;
      short_addr = (cp[0] << 8) | cp[1];
      cp += 2;
      length -= 2;
      fcf += 2;
      if (length < 8) goto trunc;
      if (ndo->ndo_vflag_ac)
        ndo->ndo_vflag(ndo, "%04x:%s ", short_addr, le64addr_string(ndo, cp));
      cp += 8;
      length -= 8;
      fcf += 8;
      break;
  }
  if (!ndo->ndo_qflag) ndo->ndo_hex_dump(ndo, cp, length);
  return (fcf);
trunc:
  ndo->ndo_vflag(ndo, "[|802.15.4]");
  return (fcf);
}