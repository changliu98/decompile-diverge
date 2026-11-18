int rx_cache_find(rx_header *rxh,ip *ip,int sport,int32_t *opcode)

{
  ushort uVar1;
  in_addr_t iVar2;
  in_addr_t iVar3;
  uint32_t uVar4;
  uint32_t uVar5;
  long lVar6;
  uint32_t sip;
  uint32_t clip;
  rx_cache_entry *rxent;
  int i;
  int32_t *opcode_local;
  int sport_local;
  ip *ip_local;
  rx_header *rxh_local;
  
  iVar2 = (ip->ip_dst).s_addr;
  iVar3 = (ip->ip_src).s_addr;
  i = rx_cache_hint;
  do {
    lVar6 = (long)i;
    uVar5 = rx_cache[lVar6].callnum;
    uVar4 = EXTRACT_32BITS(&rxh->callNumber);
    if ((((uVar5 == uVar4) && (rx_cache[lVar6].client.s_addr == iVar2)) &&
        (rx_cache[lVar6].server.s_addr == iVar3)) &&
       ((uVar1 = rx_cache[lVar6].serviceId, uVar5 = EXTRACT_32BITS(&rxh->serviceId), uVar1 == uVar5
        && (rx_cache[lVar6].dport == sport)))) {
      rx_cache_hint = i;
      *opcode = rx_cache[lVar6].opcode;
      return 1;
    }
    i = i + 1;
    if (0x3f < i) {
      i = 0;
    }
  } while (i != rx_cache_hint);
  return 0;
}