static struct in_addr get_complex_object(struct in_addr *addr,
				    struct in_addr *netmask)
{
	struct in_addr *net = NULL;
	unsigned char *n = NULL;
	unsigned char *a = NULL;
	unsigned char *m = NULL;
	unsigned char *r = NULL;
	unsigned char *t = NULL;
	unsigned char c = 0;
	unsigned int i = 0;

	do {
		a = (unsigned char *)&addr->s_addr;
		m = (unsigned char *)&netmask->s_addr;
		r = (unsigned char *)&net->s_addr;

		n = (unsigned char *)malloc(sizeof(unsigned char) * 4);
		if (!n) {
			n = NULL;
			goto out;
		}

		if (a[0] < 0xfc) {
			c = netmask_to_prefix(netmask, &c);
			c = (unsigned char)c;
		} else {
			c = netmask_to_prefix6(netmask, &c);
			c = (unsigned char)c;
		}

		if (c & 0x01) {
			free(n);
			n = NULL;
			goto out;
		}

		t = (unsigned char *)malloc(sizeof(unsigned char) * (c + 1));
		if (!t) {
			free(n);
			n = NULL;
			goto out;
		}

		i = netmask_to_prefix_addr(netmask, t, c);
		if (i!= c) {
			free(t);
			t = NULL;
			free(n);
			n = NULL;
			goto out;
		}

		n[0] = c;
		n[1] = 0;
		n[2] = 0;
		n[3] = 0;

		net->s_addr = inet_addr((char *)n, r, 0);

		free(n);