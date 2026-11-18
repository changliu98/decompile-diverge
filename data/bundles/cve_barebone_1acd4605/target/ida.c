u_int __cdecl chdlc_print(netdissect_options *ndo, const u_char *p, u_int length)
{
  const char *v3; // rax
  const char *v5; // [rsp+18h] [rbp-28h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+20h] [rbp-20h]
  u_int proto; // [rsp+28h] [rbp-18h]
  u_int lengthb; // [rsp+2Ch] [rbp-14h]
  const u_char *pa; // [rsp+30h] [rbp-10h]

  proto = EXTRACT_16BITS(p + 2);
  if ( ndo->ndo_eflag )
  {
    ndo_printf = ndo->ndo_printf;
    v5 = tok2str(&chdlc_cast_values, "0x%02x", *p);
    v3 = tok2str(&ethertype_values, "Unknown", proto);
    ndo_printf(ndo, "%s, ethertype %s (0x%04x), length %u: ", v5, v3, proto, length);
  }
  lengthb = length - 4;
  pa = p + 4;
  switch ( proto )
  {
    case 0x800u:
      ip_print(ndo, pa, lengthb);
      break;
    case 0x8035u:
      chdlc_slarp_print(ndo, pa, lengthb);
      break;
    case 0x86DDu:
      ip6_print(ndo, pa, lengthb);
      break;
    default:
      if ( proto - 34887 < 2 )
      {
        mpls_print(ndo, pa, lengthb);
      }
      else if ( proto == 65278 )
      {
        if ( p[5] == 129 || p[5] == 130 || p[5] == 131 )
          isoclns_print(ndo, p + 5, lengthb - 1, LODWORD(ndo->ndo_snapend) - ((_DWORD)p + 4) - 1);
        else
          isoclns_print(ndo, pa, lengthb, (u_int)&ndo->ndo_snapend[-(_DWORD)pa]);
      }
      else if ( !ndo->ndo_eflag )
      {
        ndo->ndo_printf(ndo, "unknown CHDLC protocol (0x%04x)", proto);
      }
      break;
  }
  return 4;
}