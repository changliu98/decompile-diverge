void __cdecl bgp_capabilities_print(netdissect_options *ndo, const u_char *opt, int caps_len)
{
  int i, cap_len, tcap_len, cap_offset;
  unsigned int cap_type;
  const char *cap_str, *afi_str, *safi_str, *flag_str;
  char *as_str;

  for (i = 0; i < caps_len; i += cap_len + 2)
  {
    // Bounds check: Ensure we can read the 2-byte capability header
    if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || &opt[i] > ndo->ndo_snapend - 2)
      goto trunc;

    cap_type = opt[i];
    cap_len = opt[i + 1];
    tcap_len = cap_len;

    cap_str = tok2str(&bgp_capcode_values, "Unknown", cap_type);
    ndo->ndo_printf(ndo, "\n\t      %s (%u), length: %u", cap_str, cap_type, (unsigned int)cap_len);

    // Bounds check: Ensure the capability body is within snapend
    if (&ndo->ndo_snapend[-cap_len] > ndo->ndo_snapend || &opt[i + 2] > &ndo->ndo_snapend[-cap_len])
      goto trunc;

    if (cap_type == 1) // BGP Capability Code 1: Multiprotocol Extensions
    {
      afi_str = tok2str(&af_values, "Unknown", _byteswap_ushort(*(_WORD *)&opt[i + 2]));
      safi_str = tok2str(&bgp_safi_values, "Unknown", opt[i + 5]);
      ndo->ndo_printf(
          ndo,
          "\n\t\tAFI %s (%u), SAFI %s (%u)",
          afi_str,
          _byteswap_ushort(*(_WORD *)&opt[i + 2]),
          safi_str,
          opt[i + 5]);
    }
    else if (cap_type != 2) // BGP Capability Code 2: Route Refresh (No specific decoder needed here)
    {
      switch (cap_type)
      {
        case 64: // '@' - BGP Capability Code 64: Graceful Restart
          if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || &opt[i + 2] > ndo->ndo_snapend - 2)
            goto trunc;

          flag_str = "none";
          if ((opt[i + 2] & 0x80) != 0)
            flag_str = "R";

          ndo->ndo_printf(
              ndo,
              "\n\t\tRestart Flags: [%s], Restart Time %us",
              flag_str,
              _byteswap_ushort(*(_WORD *)&opt[i + 2]) & 0xFFF);

          tcap_len = cap_len - 2;
          cap_offset = 4;
          while (tcap_len >= 4)
          {
            afi_str = tok2str(&af_values, "Unknown", _byteswap_ushort(*(_WORD *)&opt[i + cap_offset]));
            safi_str = tok2str(&bgp_safi_values, "Unknown", opt[cap_offset + 2 + i]);
            
            flag_str = "no";
            if ((opt[cap_offset + 3 + i] & 0x80) != 0)
              flag_str = "yes";

            ndo->ndo_printf(
                ndo,
                "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",
                afi_str,
                _byteswap_ushort(*(_WORD *)&opt[i + cap_offset]),
                safi_str,
                opt[cap_offset + 2 + i],
                flag_str);
            
            tcap_len -= 4;
            cap_offset += 4;
          }
          break;

        case 65: // 'A' - BGP Capability Code 65: Support for 4-octet AS number
          if (cap_len == 4)
          {
            as_str = as_printf(ndo, astostr, 20, _byteswap_ulong(*(_DWORD *)&opt[i + 2]));
            ndo->ndo_printf(ndo, "\n\t\t 4 Byte AS %s", as_str);
          }
          break;

        case 69: // 'E' - BGP Capability Code 69: ADD-PATH
          cap_offset = 2;
          if (cap_len)
          {
            while (tcap_len > 0)
            {
              if (tcap_len < 4)
              {
                ndo->ndo_printf(ndo, "\n\t\t(invalid)");
                goto LABEL_41;
              }
              afi_str = tok2str(&af_values, "Unknown", _byteswap_ushort(*(_WORD *)&opt[i + cap_offset]));
              safi_str = tok2str(&bgp_safi_values, "Unknown", opt[cap_offset + 2 + i]);
              flag_str = tok2str(&bgp_add_path_recvsend, "Bogus (0x%02x)", opt[cap_offset + 3 + i]);
              
              ndo->ndo_printf(
                  ndo,
                  "\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive: %s",
                  afi_str,
                  _byteswap_ushort(*(_WORD *)&opt[i + cap_offset]),
                  safi_str,
                  opt[cap_offset + 2 + i],
                  flag_str);
              
              tcap_len -= 4;
              cap_offset += 4;
            }
          }
          else
          {
            ndo->ndo_printf(ndo, " (bogus)");
          }
          break;

        default:
          if (cap_type != 128) // BGP Capability Code 128: Route Refresh (Cisco specific, often ignored)
          {
            ndo->ndo_printf(ndo, "\n\t\tno decoder for Capability %u", cap_type);
            if (ndo->ndo_vflag <= 1)
              print_unknown_data(ndo, &opt[i + 2], "\n\t\t", cap_len);
          }
          break;
      }
    }

LABEL_41:
    if (ndo->ndo_vflag > 1 && cap_len > 0)
      print_unknown_data(ndo, &opt[i + 2], "\n\t\t", cap_len);
  }
  return;

trunc:
  ndo->ndo_printf(ndo, "[|BGP]");
}