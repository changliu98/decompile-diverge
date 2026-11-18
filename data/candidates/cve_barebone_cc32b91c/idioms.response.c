int rx_cache_find(struct rx_header *rxh, struct ip *ip, int sport, int *opcode)
{
  struct rx_cache_entry *rxent;
  int i;
  unsigned int callnum;
  unsigned int serviceId;
  unsigned int client;
  unsigned int server;
  client = ip->ip_dst.s_addr;
  server = ip->ip_src.s_addr;
  i = rx_cache_hint;
  do {
    rxent = &rx_cache[i];
    callnum = rxent->callnum;
    if (callnum == be32toh(&rxh->callNumber)) {
      if (rxent->client.s_addr == client &&
          rxent->server.s_addr == server) {
        serviceId = rxent->serviceId;
        if (serviceId == be32toh(&rxh->serviceId)) {
          if (rxent->dport == sport) {
            rx_cache_hint = i;
            *opcode = rxent->opcode;
            return 1;
          }
        }
      }
    }
    i++;
    if (i >= 64)
      i = 0;
  } while (i != rx_cache_hint);
  return 0;
}