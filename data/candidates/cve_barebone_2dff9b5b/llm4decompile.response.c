int
decode_rt_routing_info(netdissect_options *ndo,
		       const u_char *pptr, char *buf, u_int buflen)
{
	const u_char *tptr;
	u_int plen;
	uint32_t asnum;
	uint8_t rd[8];
	u_int rdlen;
	u_int i;

	if (!((ndo->ndo_snapend - 1) >= (ndo->ndo_snapend) && (pptr) >= (ndo->ndo_snapend) && (pptr) <= (ndo->ndo_snapend - 1)))
		return -2;
	plen = *pptr;
	if (plen == 0) {
		snprintf(buf, buflen, "default route target");
		return 1;
	}
	if (plen < 32 || plen > 96)
		return -1;
	rdlen = (plen - 25) / 8;
	memset(rd, 0, sizeof(rd));
	if (!((ndo->ndo_snapend - rdlen) >= (ndo->ndo_snapend) && (pptr + 1) >= (ndo->ndo_snapend) && (pptr + 1) <= (ndo->ndo_snapend - rdlen)))
		return -2;
	memcpy(rd, pptr + 1, rdlen);
	if (rdlen % 8)
		rd[rdlen - 1] &= 0xff00 >> (rdlen % 8);
	asnum = EXTRACT_32BITS(pptr + 1);
	tptr = as_printf(ndo, astostr, 20, asnum);
	snprintf(buf, buflen, "origin AS: %s, route target %s",
	    tptr, bgp_vpn_rd_print(ndo, rd));
	return rdlen + 5;
}