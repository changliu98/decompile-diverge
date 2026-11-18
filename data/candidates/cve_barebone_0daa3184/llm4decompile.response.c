struct enamemem *
lookup_bytestring(netdissect_options *ndo,
                  const u_char *bs, unsigned int nlen)
{
	register struct enamemem *p;
	register u_short a0, a1, a2;

	a0 = 0;
	a1 = 0;
	a2 = 0;
	if (nlen >= 6) {
		a0 = bs[0];
		a1 = bs[1];
		a2 = bs[2];
	}
	if (nlen >= 4) {
		a0 = bs[0];
		a1 = bs[1];
	}
	p = &bytestringtable[((a0 ^ a1) ^ a2) & (16384 - 1)];
	while (p->e_nxt) {
		if (p->e_addr0 == a0 && p->e_addr1 == a1 && p->e_addr2 == a2 &&
		    !memcmp(bs, p->e_nsap, nlen))
			return (p);
		p = p->e_nxt;
	}
	p->e_addr0 = a0;
	p->e_addr1 = a1;
	p->e_addr2 = a2;
	p->e_nsap = (u_char *)calloc(1, nlen + 1);
	if (p->e_nsap == NULL)
		(*ndo->ndo_error)(ndo, "lookup_bytestring: calloc");
	memcpy(p->e_nsap, bs, nlen);
	p->e_nxt = (struct enamemem *)calloc(1, sizeof(struct enamemem));
	if (p->e_nxt == NULL)
		(*ndo->ndo_error)(ndo, "lookup_bytestring: calloc");
	return (p);
}