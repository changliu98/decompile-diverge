void __cdecl isakmp_rfc3948_print(netdissect_options *ndo, const u_char *bp, u_int length, const u_char *bp2)
{
  int advance;
  int padlen;
  int enh;
  const u_char *inner_bp;
  u_int inner_length;

  // 1. Check for NAT-Keep-Alive packet (length 1 and payload is 0xFF)
  if ( length == 1 && bp[0] == 0xFF )
  {
    ndo->ndo_printf(ndo, "isakmp-nat-keep-alive");
    return;
  }

  // 2. Check for truncated packet
  if ( length < 4 )
  {
    ndo->ndo_printf(ndo, "[|isakmp]");
    return;
  }

  // 3. Check if it's ESP encapsulated (first 4 bytes are not all zero)
  if ( bp[0] != 0 || bp[1] != 0 || bp[2] != 0 || bp[3] != 0 )
  {
    ndo->ndo_printf(ndo, "UDP-encap: ");
    advance = esp_print(ndo, bp, length, bp2, &enh, &padlen);
    
    if ( advance > 0 )
    {
      inner_bp = bp + advance;
      inner_length = length - (padlen + advance);
      
      // `enh` holds the next header protocol ID
      ip_print_inner(ndo, inner_bp, inner_length, (unsigned __int8)enh, bp2);
    }
    return;
  }

  // 4. Otherwise, it's a NON-ESP encapsulated ISAKMP packet
  ndo->ndo_printf(ndo, "NONESP-encap: ");
  isakmp_print(ndo, bp + 4, length - 4, bp2);
}