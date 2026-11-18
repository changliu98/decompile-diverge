__attribute__((used)) static int
rx_cache_find(u_char *pkt, struct net_device *dev, u_short type, int *len)
{
	struct rx_header *rx = (struct rx_header *) pkt;
	u_long destaddr, srcaddr;
	int i, ret;

	destaddr = dev->dev_addr[4] | (dev->dev_addr[5] << 8);
	srcaddr = dev->dev_addr[2] | (dev->dev_addr[3] << 8);

	i = rx_cache_hint;
	do {
		struct rx_cache_entry *ent = &rx_cache[i];

		if (ent->destaddr == destaddr &&
		    ent->srcaddr == srcaddr &&
		    ((ent->type & 0xffff) == type) &&
		    ent->address == EXTRACT_32BITS(&rx->address) &&
		    ent->length == EXTRACT_32BITS(&rx->length)) {
			rx_cache_hint = i;
			*len = ent->len;
			ret = 1;
			goto out;
		}

		if (++i >= 64)
			i = 0;
	} while (i != rx_cache_hint);

	ret = 0;

out:
	return ret;
}