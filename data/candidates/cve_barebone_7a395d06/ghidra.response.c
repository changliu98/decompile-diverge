u_int chdlc_if_print(netdissect_options *ndo,pcap_pkthdr *h,u_char *p)

{
  u_int caplen;
  u_int length;
  u_char *p_local;
  pcap_pkthdr *h_local;
  netdissect_options *ndo_local;
  uint local_c;
  
  local_c = h->caplen;
  if (local_c < 4) {
    (*ndo->ndo_printf)(ndo,"[|chdlc]");
  }
  else {
    local_c = chdlc_print(ndo,p,h->len);
  }
  return local_c;
}