u_int __cdecl chdlc_if_print(netdissect_options *ndo, const pcap_pkthdr *h, const u_char *p)
{
  uint32_t caplen; // [rsp+8h] [rbp-28h]

  caplen = h->caplen;
  if ( caplen >= 4 )
    return chdlc_print(ndo, p, h->len);
  ndo->ndo_printf(ndo, "[|chdlc]");
  return caplen;
}