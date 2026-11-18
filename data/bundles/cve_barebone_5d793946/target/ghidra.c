int decode_multicast_vpn(netdissect_options *ndo,u_char *pptr,char *buf,u_int buflen)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint32_t uVar4;
  char *pcVar5;
  size_t sVar6;
  char *pcVar7;
  u_char *puVar8;
  u_int offset;
  uint8_t sg_length;
  uint8_t addr_length;
  uint8_t route_length;
  uint8_t route_type;
  u_int buflen_local;
  char *buf_local;
  u_char *pptr_local;
  netdissect_options *ndo_local;
  int local_c;
  
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < pptr)) {
LAB_00101a4a:
    local_c = -2;
  }
  else {
    bVar2 = *pptr;
    puVar8 = pptr + 2;
    bVar1 = pptr[1];
    pcVar5 = tok2str(bgp_multicast_vpn_route_type_values,"Unknown",(uint)bVar2);
    snprintf(buf,(ulong)buflen,"Route-Type: %s (%u), length: %u",pcVar5,(ulong)bVar2,(ulong)bVar1);
    switch(bVar2) {
    case 1:
      if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < puVar8))
      goto LAB_00101a4a;
      sVar6 = strlen(buf);
      pcVar5 = bgp_vpn_rd_print(ndo,puVar8);
      pcVar7 = bgp_vpn_ip_print(ndo,pptr + 10,(bVar1 - 8) * 8);
      snprintf(buf + (sVar6 & 0xffffffff),(ulong)(buflen - (int)sVar6),", RD: %s, Originator %s",
               pcVar5,pcVar7);
      break;
    case 2:
      if ((ndo->ndo_snapend < ndo->ndo_snapend + -0xc) || (ndo->ndo_snapend + -0xc < puVar8))
      goto LAB_00101a4a;
      sVar6 = strlen(buf);
      pcVar5 = bgp_vpn_rd_print(ndo,puVar8);
      uVar4 = EXTRACT_32BITS(pptr + 10);
      pcVar7 = as_printf(ndo,astostr,0x14,uVar4);
      snprintf(buf + (sVar6 & 0xffffffff),(ulong)(buflen - (int)sVar6),", RD: %s, Source-AS %s",
               pcVar5,pcVar7);
      break;
    case 3:
      if ((ndo->ndo_snapend + -8 <= ndo->ndo_snapend) && (puVar8 <= ndo->ndo_snapend + -8)) {
        sVar6 = strlen(buf);
        pcVar5 = bgp_vpn_rd_print(ndo,puVar8);
        snprintf(buf + (sVar6 & 0xffffffff),(ulong)(buflen - (int)sVar6),", RD: %s",pcVar5);
        puVar8 = pptr + 10;
        iVar3 = bgp_vpn_sg_print(ndo,puVar8,buf,buflen);
        bVar2 = bVar1 - (char)iVar3;
        if ((ndo->ndo_snapend + -(ulong)bVar2 <= ndo->ndo_snapend) &&
           (puVar8 <= ndo->ndo_snapend + -(ulong)bVar2)) {
          sVar6 = strlen(buf);
          pcVar5 = bgp_vpn_ip_print(ndo,puVar8,(uint)bVar2 << 3);
          snprintf(buf + (sVar6 & 0xffffffff),(ulong)(buflen - (int)sVar6),", Originator %s",pcVar5)
          ;
          break;
        }
      }
      goto LAB_00101a4a;
    case 4:
      break;
    case 5:
      if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < puVar8))
      goto LAB_00101a4a;
      sVar6 = strlen(buf);
      pcVar5 = bgp_vpn_rd_print(ndo,puVar8);
      snprintf(buf + (sVar6 & 0xffffffff),(ulong)(buflen - (int)sVar6),", RD: %s",pcVar5);
      bgp_vpn_sg_print(ndo,pptr + 10,buf,buflen);
      break;
    case 6:
    case 7:
      if ((ndo->ndo_snapend < ndo->ndo_snapend + -8) || (ndo->ndo_snapend + -8 < puVar8))
      goto LAB_00101a4a;
      sVar6 = strlen(buf);
      pcVar5 = bgp_vpn_rd_print(ndo,puVar8);
      uVar4 = EXTRACT_32BITS(pptr + 10);
      pcVar7 = as_printf(ndo,astostr,0x14,uVar4);
      snprintf(buf + (sVar6 & 0xffffffff),(ulong)(buflen - (int)sVar6),", RD: %s, Source-AS %s",
               pcVar5,pcVar7);
      bgp_vpn_sg_print(ndo,pptr + 10,buf,buflen);
    }
    local_c = bVar1 + 2;
  }
  return local_c;
}