void __cdecl ripng_print(netdissect_options *ndo, const u_char *dat, unsigned int length)
{
  unsigned int snapend_offset;
  unsigned int remaining_len;
  unsigned int num_entries;
  const netinfo6 *ni;
  bool is_dump_req;
  bool is_truncated;

  // Check if packet data is within the captured snapend bounds
  if ( ndo->ndo_snapend < dat )
    return;

  // Calculate the valid length of the packet data up to snapend
  snapend_offset = (unsigned int)ndo->ndo_snapend - (unsigned int)dat;
  if ( length > snapend_offset )
    length = snapend_offset;

  // RIPng header is 4 bytes; ensure we have at least that
  if ( length < 4 )
    return;

  remaining_len = length - 4;
  num_entries = length / 20;

  // RIPng Command
  if ( dat[0] == 1 ) // Request
  {
    // Check for "dump" request (single entry, metric is 16, and prefix/route tag are zero)
    if ( num_entries == 1 && dat[23] == 16 )
    {
      is_dump_req = true;
      if ( *((_DWORD *)dat + 1) == 0 )
      {
        is_dump_req = true;
        if ( *((_DWORD *)dat + 2) == 0 )
        {
          is_dump_req = true;
          if ( *((_DWORD *)dat + 3) == 0 )
            is_dump_req = (*((_DWORD *)dat + 4) == 0);
        }
      }
    }
    else
    {
      is_dump_req = false;
    }

    if ( is_dump_req )
    {
      ndo->ndo_printf(ndo, " ripng-req dump", length % 20);
    }
    else
    {
      if ( 20 * num_entries == length - 4 )
        ndo->ndo_printf(ndo, " ripng-req %d:", num_entries);
      else
        ndo->ndo_printf(ndo, " ripng-req %d[%u]:", num_entries, length);

      ni = (const netinfo6 *)(dat + 4);
      while ( remaining_len >= 20 )
      {
        if ( ndo->ndo_vflag <= 1 )
          ndo->ndo_printf(ndo, " ", remaining_len % 20);
        else
          ndo->ndo_printf(ndo, "\n\t", remaining_len % 20);

        rip6_entry_print(ndo, ni, 0);
        remaining_len -= 20;
        ++ni;
      }
    }
  }
  else if ( dat[0] == 2 ) // Response
  {
    if ( 20 * num_entries == length - 4 )
      ndo->ndo_printf(ndo, " ripng-resp %d:", num_entries);
    else
      ndo->ndo_printf(ndo, " ripng-resp %d[%u]:", num_entries, length);

    is_truncated = (20 * (remaining_len / 20) != remaining_len);
    ni = (const netinfo6 *)(dat + 4);
    while ( remaining_len >= 20 )
    {
      if ( ndo->ndo_vflag <= 1 )
        ndo->ndo_printf(ndo, " ", remaining_len % 20);
      else
        ndo->ndo_printf(ndo, "\n\t", remaining_len % 20);

      rip6_entry_print(ndo, ni, ni->rip6_metric);
      remaining_len -= 20;
      ++ni;
    }

    if ( is_truncated )
      ndo->ndo_printf(ndo, "[|ripng]", remaining_len % 20);
  }
  else // Unknown Command
  {
    ndo->ndo_printf(ndo, " ripng-%d ?? %u", dat[0], length);
  }

  // RIPng version is expected to be 1
  if ( dat[1] != 1 )
    ndo->ndo_printf(ndo, " [vers %d]", dat[1]);
}