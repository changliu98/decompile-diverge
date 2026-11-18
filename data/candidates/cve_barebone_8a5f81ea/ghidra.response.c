u_int pktap_if_print(netdissect_options *ndo,pcap_pkthdr *h,u_char *p)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  uint length_00;
  u_int uVar6;
  if_printer p_Var7;
  pktap_header_t *hdr;
  if_printer printer;
  u_int length;
  u_int caplen;
  uint32_t rectype;
  uint32_t hdrlen;
  uint32_t dlt;
  u_char *p_local;
  pcap_pkthdr *h_local;
  netdissect_options *ndo_local;
  uint local_c;
  
  uVar5 = h->caplen;
  length_00 = h->len;
  if ((uVar5 < 0x6c) || (length_00 < 0x6c)) {
    (*ndo->ndo_printf)(ndo,"[|pktap]");
    local_c = 0;
  }
  else {
    bVar1 = p[0xb];
    bVar2 = p[10];
    bVar3 = p[9];
    bVar4 = p[8];
    hdrlen = (uint)p[3] << 0x18 | (uint)p[2] << 0x10 | (uint)p[1] << 8 | (uint)*p;
    if (hdrlen < 0x6c) {
      (*ndo->ndo_printf)(ndo,"[|pktap]");
      local_c = 0;
    }
    else if ((uVar5 < hdrlen) || (length_00 < hdrlen)) {
      (*ndo->ndo_printf)(ndo,"[|pktap]");
      local_c = hdrlen;
    }
    else {
      if (ndo->ndo_eflag != 0) {
        pktap_header_print(ndo,p,length_00);
      }
      if (*(int *)(p + 4) == 0) {
        (*ndo->ndo_printf)(ndo,"no data");
      }
      else if (*(int *)(p + 4) == 1) {
        p_Var7 = lookup_printer((uint)bVar1 << 0x18 | (uint)bVar2 << 0x10 | (uint)bVar3 << 8 |
                                (uint)bVar4);
        if (p_Var7 == (if_printer)0x0) {
          if (ndo->ndo_eflag == 0) {
            pktap_header_print(ndo,p,length_00);
          }
          if (ndo->ndo_suppress_default_print == 0) {
            (*ndo->ndo_default_print)(ndo,p + hdrlen,uVar5 - hdrlen);
          }
        }
        else {
          uVar6 = (*p_Var7)(ndo,h,p + hdrlen);
          hdrlen = uVar6 + hdrlen;
        }
      }
      local_c = hdrlen;
    }
  }
  return local_c;
}