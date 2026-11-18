u_int __cdecl ieee802_15_4_if_print(netdissect_options *ndo, const pcap_pkthdr *h, const u_char *p)
{
  uint16_t panid = 0;
  uint8_t seq;
  uint16_t fc;
  u_int hdrlen;
  bpf_u_int32 caplen = h->caplen;
  const u_char *payload;
  u_int payload_len;
  u_int ret_len;

  if (caplen < 3)
  {
    ndo->ndo_printf(ndo, "[|802.15.4]");
    return caplen;
  }

  hdrlen = 3;
  fc = *(_WORD *)p;
  seq = p[2];
  payload = p + 3;
  payload_len = caplen - 3;

  // Frame Type is bits 0-2
  ndo->ndo_printf(ndo, "IEEE 802.15.4 %s packet ", (&ftypes)[fc & 0x0007]);

  if (ndo->ndo_vflag)
    ndo->ndo_printf(ndo, "seq %02x ", seq);

  // Destination Addressing Mode is bits 10-11
  switch ((fc >> 10) & 3)
  {
    case 0:
      if ((fc & 0x0040) != 0) // PAN ID Compression
        goto LABEL_47;
      if (ndo->ndo_vflag)
        ndo->ndo_printf(ndo, "none ");
      goto LABEL_25;

    case 1:
      if (ndo->ndo_vflag)
        ndo->ndo_printf(ndo, "reserved destination addressing mode");
      return 3;

    case 2:
      if (payload_len < 2)
        goto LABEL_47;
      panid = *(_WORD *)payload;
      payload += 2;
      payload_len -= 2;
      hdrlen = 5;

      if (payload_len < 2)
        goto LABEL_47;
      if (ndo->ndo_vflag)
        ndo->ndo_printf(ndo, "%04x:%04x ", panid, *(unsigned __int16 *)payload);
      
      payload += 2;
      payload_len -= 2;
      hdrlen = 7;
      goto LABEL_25;

    case 3:
      if (payload_len < 2)
        goto LABEL_47;
      
      panid = *(_WORD *)payload;
      payload += 2;
      payload_len -= 2;
      hdrlen = 5;

      if (payload_len < 8)
      {
LABEL_47:
        ndo->ndo_printf(ndo, "[|802.15.4]");
        ret_len = hdrlen;
      }
      else
      {
        if (ndo->ndo_vflag)
          ndo->ndo_printf(ndo, "%04x:%s ", panid, le64addr_string(ndo, payload));
        
        payload += 8;
        payload_len -= 8;
        hdrlen = 13;

LABEL_25:
        if (ndo->ndo_vflag)
          ndo->ndo_printf(ndo, "< ");

        // Source Addressing Mode is bits 14-15
        switch (fc >> 14)
        {
          case 0:
            if (ndo->ndo_vflag)
              ndo->ndo_printf(ndo, "none ");
            break;

          case 1:
            if (ndo->ndo_vflag)
              ndo->ndo_printf(ndo, "reserved source addressing mode");
            return 0;

          case 2:
            if ((fc & 0x0040) == 0) // No PAN ID Compression
            {
              if (payload_len < 2)
                goto LABEL_47;
              panid = *(_WORD *)payload;
              payload += 2;
              payload_len -= 2;
              hdrlen += 2;
            }

            if (payload_len < 2)
              goto LABEL_47;
            if (ndo->ndo_vflag)
              ndo->ndo_printf(ndo, "%04x:%04x ", panid, *(unsigned __int16 *)payload);
            
            payload += 2;
            payload_len -= 2;
            hdrlen += 2;
            break;

          case 3:
            if ((fc & 0x0040) == 0) // No PAN ID Compression
            {
              if (payload_len < 2)
                goto LABEL_47;
              panid = *(_WORD *)payload;
              payload += 2;
              payload_len -= 2;
              hdrlen += 2;
            }

            if (payload_len < 8)
              goto LABEL_47;
            if (ndo->ndo_vflag)
              ndo->ndo_printf(ndo, "%04x:%s ", panid, le64addr_string(ndo, payload));
            
            payload += 8;
            payload_len -= 8;
            hdrlen += 8;
            break;

          default:
            break;
        }

        if (!ndo->ndo_suppress_default_print)
          ndo->ndo_default_print(ndo, payload, payload_len);
        
        ret_len = hdrlen;
      }
      break;

    default:
      goto LABEL_25;
  }

  return ret_len;
}