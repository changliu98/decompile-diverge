int __cdecl rx_cache_find(const rx_header *rxh, const ip *ip_0, int sport, int32_t *opcode)
{
  uint32_t target_callnum = EXTRACT_32BITS(&rxh->callNumber);
  uint32_t target_serviceId = EXTRACT_32BITS(&rxh->serviceId);
  in_addr_t target_clip = ip_0->ip_dst.s_addr; // Client IP
  in_addr_t target_sip = ip_0->ip_src.s_addr;  // Server IP

  int i = rx_cache_hint;
  
  // Iterate through the circular cache buffer
  do
  {
    rx_cache_entry *rxent = &rx_cache[i];
    
    // Check first level of cache matching criteria
    if ( rxent->callnum == target_callnum && 
         rxent->client.s_addr == target_clip && 
         rxent->server.s_addr == target_sip )
    {
      // Check second level of cache matching criteria
      if ( rxent->serviceId == target_serviceId && rxent->dport == sport )
      {
        // Cache hit: update hint for future lookups and return opcode
        rx_cache_hint = i;
        *opcode = rxent->opcode;
        return 1;
      }
    }
    
    // Advance index with wrap-around (cache size is 64)
    if ( ++i >= 64 )
      i = 0;
  }
  while ( i != rx_cache_hint );
  
  // Cache miss
  return 0;
}