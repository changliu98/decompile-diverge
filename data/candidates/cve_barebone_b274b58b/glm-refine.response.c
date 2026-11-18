u_int __cdecl mfr_print(netdissect_options *ndo, const u_char *p, u_int length)
{
  const u_char *tptr;
  const u_char *ie_data;
  u_int tlen;
  u_int ie_len;
  u_int ie_tlen;
  uint8_t ie_type;
  uint8_t ie_len_val;
  uint16_t sequence_num;
  u_int idx;
  const char *flag_str;
  const char *msg_str;

  // Check if 4 bytes can be read from p without exceeding the snapend
  if (p > ndo->ndo_snapend - 4 || ndo->ndo_snapend - 4 > ndo->ndo_snapend)
    goto trunc;

  // Check if it's a control message (FRF.16 Control)
  // Control messages have the top 3 bits set to 0xE0 and the second byte is 0
  if ((*p & 0xE0) == 0xE0 && p[1] == 0)
  {
    flag_str = bittok2str(&frf_flag_values, "none", *p & 0xE0);
    msg_str = tok2str(&mfr_ctrl_msg_values, "Unknown Message (0x%02x)", p[2]);
    ndo->ndo_printf(ndo, "FRF.16 Control, Flags [%s], %s, length %u", flag_str, msg_str, length);

    tptr = p + 3;
    tlen = length - 3;

    if (ndo->ndo_vflag)
    {
      while (tlen > 2)
      {
        // Bounds check for reading IE type and length
        if (tptr > ndo->ndo_snapend - 2 || ndo->ndo_snapend - 2 > ndo->ndo_snapend)
          goto trunc;

        ie_type = *tptr;
        ie_len_val = tptr[1];
        ie_data = tptr + 2;

        msg_str = tok2str(&mfr_ctrl_ie_values, "Unknown", ie_type);
        ndo->ndo_printf(ndo, "\n\tIE %s (%u), length %u: ", msg_str, ie_type, ie_len_val);

        // If IE type is 0 or length is <= 2, abort processing
        if (!ie_type || ie_len_val <= 2)
          return 3;

        // Bounds check for reading the IE data payload
        if (tptr > ndo->ndo_snapend - ie_len_val || ndo->ndo_snapend - ie_len_val > ndo->ndo_snapend)
          goto trunc;

        ie_len = ie_len_val - 2;
        ie_tlen = tlen - 2;

        switch (ie_type)
        {
          case 1:
          case 2:
            // Print string up to 50 chars or until null terminator
            for (idx = 0; idx < ie_len && idx < 0x32 && ie_data[idx]; ++idx)
              safeputchar(ndo, ie_data[idx]);
            break;
          case 3:
            ndo->ndo_printf(ndo, "0x%08x", EXTRACT_32BITS(ie_data));
            break;
          case 5:
            if (ie_len != 16)
            {
              if (ndo->ndo_vflag <= 1)
                print_unknown_data(ndo, ie_data, "\n\t  ", ie_len);
            }
            else
            {
              ts_print(ndo, (const struct timeval *)ie_data);
            }
            break;
          default:
            if (ndo->ndo_vflag <= 1)
              print_unknown_data(ndo, ie_data, "\n\t  ", ie_len);
            break;
        }

        if (ndo->ndo_vflag > 1)
          print_unknown_data(ndo, ie_data, "\n\t  ", ie_len);

        tlen = ie_tlen - ie_len;
        tptr = ie_data + ie_len;
      }
    }
    return 3;
  }
  else
  {
    // Fragment message (FRF.16 Frag)
    sequence_num = p[1] | ((*p & 0x1E) << 7);
    flag_str = bittok2str(&frf_flag_values, "none", *p & 0xE0);

    if ((*p & 0xE0) == 0xC0 || (*p & 0xE0) == 0x80)
    {
      ndo->ndo_printf(ndo, "FRF.16 Frag, seq %u, Flags [%s], ", sequence_num, flag_str);
      fr_print(ndo, p + 2, length - 2);
      return 2;
    }
    else
    {
      ndo->ndo_printf(ndo, "FRF.16 Frag, seq %u, Flags [%s]", sequence_num, flag_str);
      print_unknown_data(ndo, p, "\n\t", length);
      return 0;
    }
  }

trunc:
  ndo->ndo_printf(ndo, "[|mfr]");
  return length;
}