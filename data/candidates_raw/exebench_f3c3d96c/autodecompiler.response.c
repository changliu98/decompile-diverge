__attribute__((used)) static void
increment_ipv6_address(struct in6_addr *addr)
{
	int i;
	u_int32_t temp;

	for (i = 3; i >= 0; i--) {
		if (i < 0)
			break;
		temp = ntohl(addr->s6_addr32[i]) + 1;
		addr->s6_addr32[i] = htonl(temp);
		if (temp != 0)
			break;
	}
}