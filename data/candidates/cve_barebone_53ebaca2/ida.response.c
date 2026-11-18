void __cdecl isakmp_rfc3948_print(netdissect_options *ndo, const u_char *bp_0, u_int length, const u_char *bp2)
{
  int advance; // [rsp+0h] [rbp-30h]
  int padlen; // [rsp+4h] [rbp-2Ch] BYREF
  int enh; // [rsp+8h] [rbp-28h] BYREF
  int nh; // [rsp+Ch] [rbp-24h]
  const u_char *bp2a; // [rsp+10h] [rbp-20h]
  u_int lengtha; // [rsp+1Ch] [rbp-14h]
  const u_char *bp_0a; // [rsp+20h] [rbp-10h]
  netdissect_options *ndoa; // [rsp+28h] [rbp-8h]

  ndoa = ndo;
  bp_0a = bp_0;
  lengtha = length;
  bp2a = bp2;
  if ( length == 1 && *bp_0a == 255 )
  {
    ndoa->ndo_printf(ndoa, "isakmp-nat-keep-alive");
  }
  else if ( lengtha < 4 )
  {
    ndoa->ndo_printf(ndoa, "[|isakmp]");
  }
  else if ( *bp_0a || bp_0a[1] || bp_0a[2] || bp_0a[3] )
  {
    ndoa->ndo_printf(ndoa, "UDP-encap: ");
    advance = esp_print(ndoa, bp_0a, lengtha, bp2a, &enh, &padlen);
    if ( advance > 0 )
    {
      bp_0a += advance;
      lengtha -= padlen + advance;
      nh = (unsigned __int8)enh;
      ip_print_inner(ndoa, bp_0a, lengtha, (unsigned __int8)enh, bp2a);
    }
  }
  else
  {
    ndoa->ndo_printf(ndoa, "NONESP-encap: ");
    isakmp_print(ndoa, bp_0a + 4, lengtha - 4, bp2a);
  }
}