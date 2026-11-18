int
rx_cache_find(rx_header *rxh, ip *ip, int sport, int32_t *opcode)
{
	int i;
	int start_hint;
	int client, server;

	client = (ip->ip_dst).s_addr;
	server = (ip->ip_src).s_addr;
	start_hint = rx_cache_hint;
	i = start_hint;
	do {
		if ((rx_cache[i].callnum == EXTRACT_32BITS(&rxh->callNumber)) &&
		    (rx_cache[i].client.s_addr == client) &&
		    (rx_cache[i].server.s_addr == server) &&
		    (rx_cache[i].serviceId == EXTRACT_32BITS(&rxh->serviceId)) &&
		    (rx_cache[i].dport == sport)) {
			rx_cache_hint = i;
			*opcode = rx_cache[i].opcode;
			return 1;
		}
		i++;
		if (i >= 64)
			i = 0;
	} while (i != start_hint);
	return 0;
}