u_int __cdecl ieee802_11_print(
        netdissect_options *ndo,
        const u_char *p,
        u_int length,
        u_int orig_caplen,
        int pad,
        u_int fcslen)
{
  int llc_hdrlen;
  lladdr_info dst;
  lladdr_info src;
  u_int meshdrlen;
  u_int hdrlen;
  u_int caplen;
  uint16_t fc;
  int frame_type;

  caplen = orig_caplen;
  if (length < fcslen)
  {
    ndo->ndo_printf(ndo, "%s", "[|802.11]");
    return caplen;
  }

  length -= fcslen;
  if (caplen > length)
  {
    fcslen = caplen - length;
    caplen = length;
    ndo->ndo_snapend -= fcslen;
  }

  if (caplen < 2)
  {
    ndo->ndo_printf(ndo, "%s", "[|802.11]");
    return orig_caplen;
  }

  fc = *(uint16_t *)p;
  hdrlen = extract_header_length(ndo, fc);
  if (!hdrlen)
    return 0;

  if (pad)
    hdrlen = (hdrlen + 3) & 0xFFFFFFFC;

  if (ndo->ndo_Hflag && (((int)fc >> 2) & 3) == 2 && (((int)fc >> 4) & 8) != 0)
  {
    meshdrlen = extract_mesh_header_length(&p[hdrlen]);
    hdrlen += meshdrlen;
  }
  else
  {
    meshdrlen = 0;
  }

  if (caplen < hdrlen)
  {
    ndo->ndo_printf(ndo, "%s", "[|802.11]");
    return hdrlen;
  }

  if (ndo->ndo_eflag)
    ieee_802_11_hdr_print(ndo, fc, p, hdrlen, meshdrlen);

  length -= hdrlen;
  caplen -= hdrlen;
  p += hdrlen;

  src.addr_string = etheraddr_string;
  dst.addr_string = etheraddr_string;

  frame_type = (fc >> 2) & 3;
  switch (frame_type)
  {
    case 0: // Management Frame
      get_mgmt_src_dst_mac(p - hdrlen, &src.addr, &dst.addr);
      if (!mgmt_body_print(ndo, fc, src.addr, p, length))
      {
        ndo->ndo_printf(ndo, "%s", "[|802.11]");
        return hdrlen;
      }
      break;

    case 1: // Control Frame
      if (!ctrl_body_print(ndo, fc, p - hdrlen))
      {
        ndo->ndo_printf(ndo, "%s", "[|802.11]");
        return hdrlen;
      }
      break;

    case 2: // Data Frame
      if ((((int)fc >> 4) & 4) != 0)
        return hdrlen;

      if ((fc & 0x4000) != 0)
      {
        ndo->ndo_printf(ndo, "Data");
        if (!wep_print(ndo, p))
        {
          ndo->ndo_printf(ndo, "%s", "[|802.11]");
          return hdrlen;
        }
      }
      else
      {
        get_data_src_dst_mac(fc, p - hdrlen, &src.addr, &dst.addr);
        llc_hdrlen = llc_print(ndo, p, length, caplen, &src, &dst);
        if (llc_hdrlen < 0)
        {
          if (!ndo->ndo_suppress_default_print)
            ndo->ndo_default_print(ndo, p, caplen);
          llc_hdrlen = -llc_hdrlen;
        }
        hdrlen += llc_hdrlen;
      }
      break;

    default: // Case 3: Reserved/Extension Frame
      break;
  }

  return hdrlen;
}