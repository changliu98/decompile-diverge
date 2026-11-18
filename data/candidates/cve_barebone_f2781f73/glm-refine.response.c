void __cdecl bgp_capabilities_print(netdissect_options *ndo, const u_char *opt, int caps_len)
{
  int i;
  int cap_offset;
  int tcap_len;
  int cap_len;
  unsigned int cap_type;

  for (i = 0; i < caps_len; i += cap_len + 2)
  {
    // Bounds checking
    if (ndo->ndo_snapend - 2 > ndo->ndo_snapend
      || &opt[i] > ndo->ndo_snapend - 2
      || (cap_type = opt[i],
          cap_len = opt[i + 1],
          tcap_len = cap_len,
          ndo->ndo_printf(ndo, "\n\t      %s (%u), length: %u", tok2str(&bgp_capcode_values, "Unknown", cap_type), cap_type, (unsigned int)cap_len),
          &ndo->ndo_snapend[-cap_len] > ndo->ndo_snapend)
      || &opt[i + 2] > &ndo->ndo_snapend[-cap_len])
    {
      ndo->ndo_printf(ndo, "[|BGP]");
      return;
    }

    // Capability 1: Multiprotocol Extensions for BGP-4
    if (cap_type == 1)
    {
      uint16_t afi = EXTRACT_16BITS(&opt[i + 2]);
      const char *afi_str = tok2str(&af_values, "Unknown", afi);
      uint8_t safi = opt[i + 5];
      const char *safi_str = tok2str(&bgp_safi_values, "Unknown", safi);
      
      ndo->ndo_printf(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u)", afi_str, afi, safi_str, safi);
    }
    // Capability 2: Route Refresh Capability for BGP-4 (No specific handling)
    else if (cap_type != 2)
    {
      switch (cap_type)
      {
        // Capability 64 (0x40): Graceful Restart Capability
        case 64:
        {
          const char *restart_flag = (opt[i + 2] & 0x80) ? "R" : "none";
          uint16_t restart_time = EXTRACT_16BITS(&opt[i + 2]) & 0xFFF;
          
          ndo->ndo_printf(ndo, "\n\t\tRestart Flags: [%s], Restart Time %us", restart_flag, restart_time);
          
          tcap_len = cap_len - 2;
          cap_offset = 4;
          while (tcap_len >= 4)
          {
            uint16_t afi = EXTRACT_16BITS(&opt[i + cap_offset]);
            const char *afi_str = tok2str(&af_values, "Unknown", afi);
            uint8_t safi = opt[cap_offset + 2 + i];
            const char *safi_str = tok2str(&bgp_safi_values, "Unknown", safi);
            const char *fwd_state = (opt[cap_offset + 3 + i] & 0x80) ? "yes" : "no";
            
            ndo->ndo_printf(
              ndo,
              "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",
              afi_str,
              afi,
              safi_str,
              safi,
              fwd_state
            );
            tcap_len -= 4;
            cap_offset += 4;
          }
          break;
        }

        // Capability 65 (0x41): Support for 4-octet AS number Capability
        case 65:
        {
          if (cap_len == 4)
          {
            uint32_t asn = EXTRACT_32BITS(&opt[i + 2]);
            char *asn_str = as_printf(ndo, astostr, 20, asn);
            ndo->ndo_printf(ndo, "\n\t\t 4 Byte AS %s", asn_str);
          }
          break;
        }

        // Capability 69 (0x45): Enhanced Route Refresh Capability
        case 69:
        {
          cap_offset = 2;
          if (cap_len == 0)
          {
            ndo->ndo_printf(ndo, " (bogus)");
          }
          else
          {
            while (tcap_len > 0)
            {
              if (tcap_len < 4)
              {
                ndo->ndo_printf(ndo, "\n\t\t(invalid)");
                goto LABEL_38;
              }
              uint16_t afi = EXTRACT_16BITS(&opt[i + cap_offset]);
              const char *afi_str = tok2str(&af_values, "Unknown", afi);
              uint8_t safi = opt[cap_offset + 2 + i];
              const char *safi_str = tok2str(&bgp_safi_values, "Unknown", safi);
              uint8_t send_recv = opt[cap_offset + 3 + i];
              const char *send_recv_str = tok2str(&bgp_add_path_recvsend, "Bogus (0x%02x)", send_recv);
              
              ndo->ndo_printf(
                ndo,
                "\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive: %s",
                afi_str,
                afi,
                safi_str,
                safi,
                send_recv_str
              );
              tcap_len -= 4;
              cap_offset += 4;
            }
          }
          break;
        }

        // Default: Unknown or Capability 128 (0x80)
        default:
        {
          if (cap_type != 128)
          {
            ndo->ndo_printf(ndo, "\n\t\tno decoder for Capability %u", cap_type);
            if (ndo->ndo_vflag <= 1)
            {
              print_unknown_data(ndo, &opt[i + 2], "\n\t\t", cap_len);
            }
          }
          break;
        }
      }
    }

LABEL_38:
    if (ndo->ndo_vflag > 1 && cap_len > 0)
    {
      print_unknown_data(ndo, &opt[i + 2], "\n\t\t", cap_len);
    }
  }
}