static int opj_j2k_write_sod(struct sockaddr_in *sin, struct sockaddr_in6 *sin6,
		      unsigned char *addr, unsigned char *mask,
		      unsigned int bits, struct net_device *dev,
		      struct netlink_ext_ack *extack)
{
	struct in6_addr *in6_addr = (struct in6_addr *)addr;
	struct in6_addr *in6_mask = (struct in6_addr *)mask;
	unsigned int in6_bits = bits - 4;
	int err;

	if (!sin &&!sin6)
		BUG_ON_EXPENSIVE(1, "No address specified");

	if (sin6) {
		BUG_ON_EXPENSIVE(in6_addr->s6_addr32[3]!= 0x0000ffff,
				 "Invalid IPv4 address");
		in6_addr->s6_addr32[3] = 0;
		if (dev)
			dev->ifindex = 0;
		else
			sin6->sin6_addr.s6_addr32[0] = 0;
	}

	memcpy(addr + 2, sin->sin_addr.s_addr, 2);
	addr += 2;

	if (dev)
		dev->ifindex = sin->sin_port;
	else
		sin6->sin6_port = 0;

	err = ipv6_addr_embed_vlan(addr, sin->sin_port, in6_addr, in6_mask,
				   in6_bits, dev, extack);
	if (!err)
		memset(addr, 0, 2);
	else
		addr[2] += 2;

	return err;
}