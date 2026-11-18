u_int ieee802_15_4_if_print(netdissect_options *ndo,pcap_pkthdr *h,u_char *p)

{
  byte bVar1;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var2;
  ushort uVar3;
  char *pcVar4;
  uint16_t panid;
  uint8_t seq;
  uint16_t fc;
  u_int hdrlen;
  u_int caplen;
  u_char *p_local;
  pcap_pkthdr *h_local;
  netdissect_options *ndo_local;
  uint local_c;
  
  local_c = h->caplen;
  panid = 0;
  if (local_c < 3) {
    (*ndo->ndo_printf)(ndo,"[|802.15.4]");
  }
  else {
    hdrlen = 3;
    uVar3 = *(ushort *)p;
    bVar1 = p[2];
    p_local = p + 3;
    caplen = local_c - 3;
    (*ndo->ndo_printf)(ndo,"IEEE 802.15.4 %s packet ",ftypes[(int)(uVar3 & 7)]);
    if (ndo->ndo_vflag != 0) {
      (*ndo->ndo_printf)(ndo,"seq %02x ",(ulong)bVar1);
    }
    switch(uVar3 >> 10 & 3) {
    case 0:
      if ((uVar3 & 0x40) != 0) {
        (*ndo->ndo_printf)(ndo,"[|802.15.4]");
        return 3;
      }
      if (ndo->ndo_vflag != 0) {
        (*ndo->ndo_printf)(ndo,"none ");
      }
      break;
    case 1:
      if (ndo->ndo_vflag != 0) {
        (*ndo->ndo_printf)(ndo,"reserved destination addressing mode");
      }
      return 3;
    case 2:
      if (caplen < 2) {
        (*ndo->ndo_printf)(ndo,"[|802.15.4]");
        return 3;
      }
      panid = *(uint16_t *)p_local;
      if (local_c - 5 < 2) {
        (*ndo->ndo_printf)(ndo,"[|802.15.4]");
        return 5;
      }
      if (ndo->ndo_vflag != 0) {
        (*ndo->ndo_printf)(ndo,"%04x:%04x ",(ulong)panid,(ulong)*(ushort *)(p + 7));
      }
      p_local = p + 7;
      caplen = local_c - 7;
      hdrlen = 7;
      break;
    case 3:
      if (caplen < 2) {
        (*ndo->ndo_printf)(ndo,"[|802.15.4]");
        return 3;
      }
      panid = *(uint16_t *)p_local;
      if (local_c - 5 < 8) {
        (*ndo->ndo_printf)(ndo,"[|802.15.4]");
        return 5;
      }
      if (ndo->ndo_vflag != 0) {
        p_Var2 = ndo->ndo_printf;
        pcVar4 = le64addr_string(ndo,p + 5);
        (*p_Var2)(ndo,"%04x:%s ",(ulong)panid,pcVar4);
      }
      p_local = p + 0xd;
      caplen = local_c - 0xd;
      hdrlen = 0xd;
    }
    if (ndo->ndo_vflag != 0) {
      (*ndo->ndo_printf)(ndo,"< ");
    }
    switch(uVar3 >> 0xe) {
    case 0:
      if (ndo->ndo_vflag != 0) {
        (*ndo->ndo_printf)(ndo,"none ");
      }
      break;
    case 1:
      if (ndo->ndo_vflag != 0) {
        (*ndo->ndo_printf)(ndo,"reserved source addressing mode");
      }
      return 0;
    case 2:
      if ((uVar3 & 0x40) == 0) {
        if (caplen < 2) {
          (*ndo->ndo_printf)(ndo,"[|802.15.4]");
          return hdrlen;
        }
        panid = *(uint16_t *)p_local;
        p_local = p_local + 2;
        caplen = caplen - 2;
        hdrlen = hdrlen + 2;
      }
      if (caplen < 2) {
        (*ndo->ndo_printf)(ndo,"[|802.15.4]");
        return hdrlen;
      }
      if (ndo->ndo_vflag != 0) {
        (*ndo->ndo_printf)(ndo,"%04x:%04x ",(ulong)panid,(ulong)*(ushort *)p_local);
      }
      p_local = p_local + 2;
      caplen = caplen - 2;
      hdrlen = hdrlen + 2;
      break;
    case 3:
      if ((uVar3 & 0x40) == 0) {
        if (caplen < 2) {
          (*ndo->ndo_printf)(ndo,"[|802.15.4]");
          return hdrlen;
        }
        panid = *(uint16_t *)p_local;
        p_local = p_local + 2;
        caplen = caplen - 2;
        hdrlen = hdrlen + 2;
      }
      if (caplen < 8) {
        (*ndo->ndo_printf)(ndo,"[|802.15.4]");
        return hdrlen;
      }
      if (ndo->ndo_vflag != 0) {
        p_Var2 = ndo->ndo_printf;
        pcVar4 = le64addr_string(ndo,p_local);
        (*p_Var2)(ndo,"%04x:%s ",(ulong)panid,pcVar4);
      }
      p_local = p_local + 8;
      caplen = caplen - 8;
      hdrlen = hdrlen + 8;
    }
    if (ndo->ndo_suppress_default_print == 0) {
      (*ndo->ndo_default_print)(ndo,p_local,caplen);
    }
    local_c = hdrlen;
  }
  return local_c;
}