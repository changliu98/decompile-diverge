__attribute__((used)) static int
ospf6_print_lshdr(struct ospf6_base *base, u_char *cp, u_char *ep)
{
	struct netdissect_options *ndo = base->base.ndo;
	int type, ret;

	if (cp + 20 > ep)
		goto trunc;
	if (base->base.caplen < base->base.hdr_len - 2 ||
	    cp + 2 > base->base.caplen - base->base.hdr_len + 2)
		goto trunc;
	ND_PRINT((ndo, "\n\t  Advertising Router %s, seq 0x%08x, "
	    "checksum 0x%04x",
	    ipaddr_string(base, cp + 8),
	    EXTRACT_32BITS(cp + 4),
	    EXTRACT_16BITS(cp)));
	type = EXTRACT_16BITS(cp);
	ret = ospf6_print_ls_type(base, type, cp + 2);

	return ret;

trunc:
	return 1;
}