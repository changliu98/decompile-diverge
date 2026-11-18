int __cdecl rx_cache_find(const rx_header *rxh, const ip *ip_0, int sport, int32_t *opcode)
{
  int serviceId; // [rsp+8h] [rbp-48h]
  uint32_t callnum; // [rsp+Ch] [rbp-44h]
  in_addr_t sip; // [rsp+10h] [rbp-40h]
  in_addr_t clip; // [rsp+14h] [rbp-3Ch]
  rx_cache_entry *rxent; // [rsp+18h] [rbp-38h]
  int i; // [rsp+24h] [rbp-2Ch]

  clip = ip_0->ip_dst.s_addr;
  sip = ip_0->ip_src.s_addr;
  i = rx_cache_hint;
  do
  {
    rxent = (rx_cache_entry *)((char *)&rx_cache + 24 * i);
    callnum = rxent->callnum;
    if ( callnum == EXTRACT_32BITS(&rxh->callNumber) && rxent->client.s_addr == clip && rxent->server.s_addr == sip )
    {
      serviceId = rxent->serviceId;
      if ( serviceId == EXTRACT_32BITS(&rxh->serviceId) && rxent->dport == sport )
      {
        rx_cache_hint = i;
        *opcode = rxent->opcode;
        return 1;
      }
    }
    if ( ++i >= 64 )
      i = 0;
  }
  while ( i != rx_cache_hint );
  return 0;
}