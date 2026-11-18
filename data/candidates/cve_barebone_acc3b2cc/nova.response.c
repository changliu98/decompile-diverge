static int sock_initaddress(struct in_addr *addr, struct in_addr *mask,
			  struct in_addr *gateway, struct in_addr *netmask,
			  struct in_addr *broadcast, int flags)
{
	struct in_addr *addrs[] = { addr, mask, gateway, netmask, broadcast };
	int ret;

	for (;;) {
		ret = get_config(addrs, (flags & RTF_REJECT)?
				 "route4" : "route4_local",
				 addr? &addr->s_addr : NULL,
				 mask? &mask->s_addr : NULL,
				 gateway? &gateway->s_addr : NULL,
				 flags);
		if (ret) {
			if (addr && mask) {
				ret = inet_aton(addr->s_addr? addr->s_addr : "",
						&addrs[0]->s_addr);
				if (ret) {
					snprintf(errbuf, sizeof(errbuf),
						 "sock_initaddress: %s is not an "
						 "IP address",
						 addr->s_addr? addr->s_addr : "");
					ret = -1;
					goto out;
				}
			}
			if (addrs[0]->s_addr == 1 && addrs[1]->s_addr == 10) {
				if (broadcast) {
					snprintf(errbuf, sizeof(errbuf),
						 "sock_initaddress: %s is not a "
						 "broadcast address",
						 broadcast->s_addr?
						 broadcast->s_addr : "");
					ret = -1;
					goto out;
				}
				ret = 0;
				goto out;
			}
			if (broadcast)
				strcpy(errbuf, "sock_initaddress: no broadcast address "
				       "for this route");
			ret = -1;
			goto out;
		}
		if (addrs[0]->s_addr == 1 && addrs[1]->s_addr == 255)
			break;
	}