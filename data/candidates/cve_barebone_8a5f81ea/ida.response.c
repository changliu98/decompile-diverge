u_int __cdecl pktap_if_print(netdissect_options *ndo, const pcap_pkthdr *h, const u_char *p)
{
  if_printer printer; // [rsp+10h] [rbp-40h]
  bpf_u_int32 length; // [rsp+1Ch] [rbp-34h]
  u_int lengtha; // [rsp+1Ch] [rbp-34h]
  u_int caplen; // [rsp+20h] [rbp-30h]
  u_int caplena; // [rsp+20h] [rbp-30h]
  unsigned int hdrlen; // [rsp+28h] [rbp-28h]
  uint32_t dlt; // [rsp+2Ch] [rbp-24h]
  const u_char *pb; // [rsp+30h] [rbp-20h]

  caplen = h->caplen;
  length = h->len;
  if ( caplen >= 0x6CuLL
    && length >= 0x6CuLL
    && (dlt = p[8] | (p[9] << 8) | (p[10] << 16) | (p[11] << 24),
        hdrlen = *p | (p[1] << 8) | (p[2] << 16) | (p[3] << 24),
        hdrlen >= 0x6CuLL) )
  {
    if ( caplen >= hdrlen && length >= hdrlen )
    {
      if ( ndo->ndo_eflag )
        pktap_header_print(ndo, p, length);
      lengtha = length - hdrlen;
      caplena = caplen - hdrlen;
      pb = &p[hdrlen];
      if ( *((_DWORD *)p + 1) )
      {
        if ( *((_DWORD *)p + 1) == 1 )
        {
          printer = lookup_printer(dlt);
          if ( printer )
          {
            hdrlen += printer(ndo, h, pb);
          }
          else
          {
            if ( !ndo->ndo_eflag )
              pktap_header_print(ndo, p, hdrlen + lengtha);
            if ( !ndo->ndo_suppress_default_print )
              ndo->ndo_default_print(ndo, pb, caplena);
          }
        }
      }
      else
      {
        ndo->ndo_printf(ndo, "no data");
      }
      return hdrlen;
    }
    else
    {
      ndo->ndo_printf(ndo, "[|pktap]");
      return hdrlen;
    }
  }
  else
  {
    ndo->ndo_printf(ndo, "[|pktap]");
    return 0;
  }
}