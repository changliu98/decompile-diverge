void __cdecl eap_print(netdissect_options *ndo, const u_char *cp, u_int length)
{
  const u_char *tptr;
  u_int type, subtype;
  int len, count;

  // Check if the packet is truncated (less than 4 bytes available)
  if (ndo->ndo_snapend - 4 > ndo->ndo_snapend || cp > ndo->ndo_snapend - 4)
    goto trunc;

  // Less verbose output
  if (ndo->ndo_vflag < 1)
  {
    ndo->ndo_printf(ndo, "%s (%u) v%u, len %u", 
                    tok2str(&eap_frame_type_values, "unknown", cp[1]),
                    cp[1], 
                    cp[0], 
                    ntohs(*(const u_short *)(cp + 2)));
    return;
  }

  // Verbose output
  ndo->ndo_printf(ndo, "%s (%u) v%u, len %u", 
                  tok2str(&eap_frame_type_values, "unknown", cp[1]),
                  cp[1], 
                  cp[0], 
                  ntohs(*(const u_short *)(cp + 2)));

  tptr = cp + 4;

  // Process EAP Request/Response (code 0)
  if (cp[1] == 0)
  {
    type = tptr[0];
    len = ntohs(*(const u_short *)(cp + 6));

    ndo->ndo_printf(ndo, ", %s (%u), id %u, len %u", 
                    tok2str(&eap_code_values, "unknown", type),
                    type, 
                    cp[5], 
                    (unsigned int)len);

    // Check if the claimed length exceeds the captured packet length
    if (&ndo->ndo_snapend[-len] > ndo->ndo_snapend || tptr > &ndo->ndo_snapend[-len])
      goto trunc;

    if (type <= 2)
    {
      subtype = cp[8];
      ndo->ndo_printf(ndo, "\n\t\t Type %s (%u)", 
                      tok2str(&eap_type_values, "unknown", subtype),
                      cp[8]);

      switch (subtype)
      {
        case 1: // Identity
          if (len - 5 > 0)
          {
            ndo->ndo_printf(ndo, ", Identity: ");
            safeputs(ndo, cp + 9, len - 5);
          }
          break;

        case 2: // Notification
          if (len - 5 > 0)
          {
            ndo->ndo_printf(ndo, ", Notification: ");
            safeputs(ndo, cp + 9, len - 5);
          }
          break;

        case 3: // Legacy NAK
          for (count = 5; count < len; ++count)
          {
            ndo->ndo_printf(ndo, " %s (%u),", 
                            tok2str(&eap_type_values, "unknown", tptr[count]),
                            tptr[count]);
          }
          return;

        default:
          // Subtypes 4, 5, 6 (unhandled, fallthrough/return)
          if (subtype - 4 < 3)
            return;

          if (subtype != 13)
          {
            if (subtype == 18)
              goto aka_subtype;

            if (subtype == 21) // TTLS
            {
              ndo->ndo_printf(ndo, " TTLSv%u", cp[9] & 7);
            }
            else if (subtype != 23)
            {
              if (subtype == 43) // FAST
              {
                ndo->ndo_printf(ndo, " FASTv%u", cp[9] & 7);
              }
              else
              {
                return;
              }
            }
          }
          
          // Common TLS flags printing for TLS (13), TTLS (21), FAST (43)
          ndo->ndo_printf(ndo, " flags [%s] 0x%02x,", 
                          bittok2str(&eap_tls_flags_values, "none", cp[9]),
                          cp[9]);

          // If the Length flag (0x80) is set, print the explicit length
          if ((cp[9] & 0x80) >> 7)
            ndo->ndo_printf(ndo, " len %u", ntohl(*(const u_int *)(cp + 10)));
          break;

aka_subtype:
          // AKA (18) and AKA' (23) subtype printing
          ndo->ndo_printf(ndo, " subtype [%s] 0x%02x,", 
                          tok2str(&eap_aka_subtype_values, "unknown", cp[9]),
                          cp[9]);
          return;
      }
    }
  }
  return;

trunc:
  ndo->ndo_printf(ndo, "\n\t[|EAP]");
}