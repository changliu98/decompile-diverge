static int rx_cache_find(RxPacket *p, struct in_addr *ip, int port,
                         int *socket) {
  int i;
  RxCacheEntry *e;
  unsigned int saddr = ip->s_addr.l;
  unsigned int daddr = ip->s_net.l;
  i = rx_cache_next;
  do {
    e = &rx_cache[i];
    if (e->id == EXTRACT_32BITS(&p->id_seq) && e->saddr == saddr &&
        e->daddr == daddr && e->port == EXTRACT_32BITS(&p->port_len) &&
        e->port_type == port) {
      rx_cache_next = i;
      *socket = e->socket;
      return 1;
    }
    i++;
    if (i >= 64) i = 0;
  } while (i != rx_cache_next);
  return 0;
}