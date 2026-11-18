int __cdecl mp_dss_print(netdissect_options *ndo, const u_char *opt, u_int opt_len, u_char flags)
{
  const u_char *cur_opt;
  uint64_t val64;
  uint32_t val32;
  uint16_t val16;

  // Check for invalid length or specific flag bit (e.g. flags & 0x02)
  if ( (opt_len != mp_dss_len((const mp_dss *)opt, 1) && opt_len != mp_dss_len((const mp_dss *)opt, 0))
    || (flags & 2) != 0 )
  {
    return 0;
  }

  // Check and print FIN flag (4th byte, bit 4)
  if ( (opt[3] & 0x10) != 0 )
    ndo->ndo_printf(ndo, " fin");

  cur_opt = opt + 4;

  // Check and print ACK (4th byte, bit 0)
  if ( (opt[3] & 1) != 0 )
  {
    ndo->ndo_printf(ndo, " ack ");
    if ( (opt[3] & 2) != 0 )  // 64-bit ACK (bit 1)
    {
      val64 = EXTRACT_64BITS(cur_opt);
      ndo->ndo_printf(ndo, "%lu", val64);
      cur_opt += 8;
    }
    else                      // 32-bit ACK
    {
      val32 = EXTRACT_32BITS(cur_opt);
      ndo->ndo_printf(ndo, "%u", val32);
      cur_opt += 4;
    }
  }

  // Check and print SEQ (4th byte, bit 2)
  if ( (opt[3] & 4) != 0 )
  {
    ndo->ndo_printf(ndo, " seq ");
    if ( (opt[3] & 8) != 0 )  // 64-bit SEQ (bit 3)
    {
      val64 = EXTRACT_64BITS(cur_opt);
      ndo->ndo_printf(ndo, "%lu", val64);
      cur_opt += 8;
    }
    else                      // 32-bit SEQ
    {
      val32 = EXTRACT_32BITS(cur_opt);
      ndo->ndo_printf(ndo, "%u", val32);
      cur_opt += 4;
    }

    // Subsequence (always 32-bit)
    val32 = EXTRACT_32BITS(cur_opt);
    ndo->ndo_printf(ndo, " subseq %u", val32);
    cur_opt += 4;

    // Length (always 16-bit)
    val16 = EXTRACT_16BITS(cur_opt);
    ndo->ndo_printf(ndo, " len %u", val16);
    cur_opt += 2;

    // Checksum (printed only if length matches the 1st `mp_dss_len` variant)
    if ( opt_len == mp_dss_len((const mp_dss *)opt, 1) )
    {
      val16 = EXTRACT_16BITS(cur_opt);
      ndo->ndo_printf(ndo, " csum 0x%x", val16);
    }
  }

  return 1;
}