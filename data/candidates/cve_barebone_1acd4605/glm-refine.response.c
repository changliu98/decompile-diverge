u_int __cdecl chdlc_print(netdissect_options *ndo, const u_char *p, u_int length)
{
  u_int proto;
  u_int lengthb;
  const u_char *pa;

  // Extract the 16-bit protocol identifier starting at offset 2
  proto = EXTRACT_16BITS(p + 2);
  
  // If the extended flag is set, print the CHDLC header information
  if (ndo->ndo_eflag)
  {
    const char *cast_str = tok2str(&chdlc_cast_values, "0x%02x", *p);
    const char *ethertype_str = tok2str(&ethertype_values, "Unknown", proto);
    ndo->ndo_printf(ndo, "%s, ethertype %s (0x%04x), length %u: ", cast_str, ethertype_str, proto, length);
  }

  // Calculate the payload length and pointer (skipping the 4-byte CHDLC header)
  lengthb = length - 4;
  pa = p + 4;

  // Route to the appropriate protocol printer based on the protocol ID
  switch (proto)
  {
    case 0x800:       // ETHERTYPE_IP (IPv4)
      ip_print(ndo, pa, lengthb);
      break;
    case 0x8035:      // ETHERTYPE_REVARP / CHDLC SLARP
      chdlc_slarp_print(ndo, pa, lengthb);
      break;
    case 0x86DD:      // ETHERTYPE_IPV6 (IPv6)
      ip6_print(ndo, pa, lengthb);
      break;
    case 0x8847:      // ETHERTYPE_MPLS (Unicast)
    case 0x8848:      // ETHERTYPE_MPLS_MCAST (Multicast)
      mpls_print(ndo, pa, lengthb);
      break;
    case 0xFEFE:      // ETHERTYPE_TRANS_ETHER / CHDLC IS-IS
      {
        // Check the NLPID (Network Layer Protocol ID) at the start of the payload
        if (p[4] == 0x81 || p[4] == 0x82 || p[4] == 0x83) // 129, 130, 131
        {
          // Active IS-IS
          isoclns_print(ndo, p + 5, lengthb - 1, (u_int)(ndo->ndo_snapend - (p + 5)));
        }
        else
        {
          // Passive IS-IS or other CLNS
          isoclns_print(ndo, pa, lengthb, (u_int)(ndo->ndo_snapend - pa));
        }
      }
      break;
    default:
      if (!ndo->ndo_eflag)
      {
        ndo->ndo_printf(ndo, "unknown CHDLC protocol (0x%04x)", proto);
      }
      break;
  }

  return 4; // Return the size of the CHDLC header
}