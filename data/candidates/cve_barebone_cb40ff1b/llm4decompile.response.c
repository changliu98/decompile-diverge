int
isis_print_mt_capability_subtlv(netdissect_options *ndo,
				const u_char *tptr, u_int len)
{
	const u_char *cp;
	u_int subtlv_type, subtlv_len;
	u_int no_of_trees;
	u_int i;

	cp = tptr;

	while (len >= 3) {
		subtlv_type = *cp++;
		subtlv_len = *cp++;
		(*ndo->ndo_printf)(ndo, "\n\t      %s subTLV #%u, length: %u",
				   tok2str(isis_mt_capability_subtlv_values,
					   "unknown", subtlv_type),
				   subtlv_type, subtlv_len);

		switch (subtlv_type) {
		case 1:
			if (cp + 20 > ndo->ndo_snapend)
				goto trunc;
			(*ndo->ndo_printf)(ndo, "\n\t        CIST Root-ID: %08x",
					   (uint32_t)(*cp++ << 24) |
					   (uint32_t)(*cp++ << 16) |
					   (uint32_t)(*cp++ << 8) |
					   (uint32_t)(*cp++));
			(*ndo->ndo_printf)(ndo, "%08x",
					   (uint32_t)(*cp++ << 24) |
					   (uint32_t)(*cp++ << 16) |
					   (uint32_t)(*cp++ << 8) |
					   (uint32_t)(*cp++));
			(*ndo->ndo_printf)(ndo, ", Path Cost: %08x",
					   (uint32_t)(*cp++ << 24) |
					   (uint32_t)(*cp++ << 16) |
					   (uint32_t)(*cp++ << 8) |
					   (uint32_t)(*cp++));
			(*ndo->ndo_printf)(ndo, ", Prio: %d",
					   (uint32_t)(*cp++ << 8) |
					   (uint32_t)(*cp++));
			(*ndo->ndo_printf)(ndo, "\n\t        RES: %d",
					   (uint32_t)(*cp >> 5));
			(*ndo->ndo_printf)(ndo, ", V: %d",
					   (uint32_t)((*cp >> 4) & 0x1));
			(*ndo->ndo_printf)(ndo, ", SPSource-ID: %d",
					   (uint32_t)((*cp++ & 0xf) << 16) |
					   (uint32_t)(*cp++ << 8) |
					   (uint32_t)(*cp++));
			(*ndo->ndo_printf)(ndo, ", No of Trees: %x",
					   *cp++);
			no_of_trees = *cp++;
			len -= 20;
			while (no_of_trees) {
				if (cp + 8 > ndo->ndo_snapend)
					goto trunc;
				(*ndo->ndo_printf)(ndo,
						   "\n\t         U:%d, M:%d, A:%d, RES:%d",
						   (uint32_t