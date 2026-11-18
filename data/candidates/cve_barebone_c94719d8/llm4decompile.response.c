void
ripng_print(netdissect_options *ndo,
	    const u_char *dat, u_int length)
{
	u_int i, j;
	const struct rip6 *rp;
	const struct rip6_entry *re;

	if (dat > ndo->ndo_snapend)
		return;
	if (length > (u_int)(ndo->ndo_snapend - dat))
		length = ndo->ndo_snapend - dat;
	if (length < sizeof(*rp))
		return;
	length -= sizeof(*rp);
	rp = (const struct rip6 *)dat;
	dat += sizeof(*rp);

	switch (rp->rip6_cmd) {

	case 1:
		/*
		 * RIPv2 request.
		 */
		i = length / sizeof(*re);
		if (i == 1 && dat[sizeof(*re) - 1] == 16 &&
		    dat[0] == 0 && dat[1] == 0 && dat[2] == 0 &&
		    dat[3] == 0) {
			/*
			 * RIPv2 request for a single entry with
			 * a metric of 16, which is used by
			 * traceroute.
			 */
			(*ndo->ndo_printf)(ndo, " ripng-req dump");
			break;
		}
		if (i * sizeof(*re) == length)
			(*ndo->ndo_printf)(ndo, " ripng-req %d:", i);
		else
			(*ndo->ndo_printf)(ndo, " ripng-req %d[%u]:", i,
			    length + sizeof(*rp));
		re = (const struct rip6_entry *)dat;
		for (j = 0; j < i; j++) {
			if (ndo->ndo_vflag >= 2)
				(*ndo->ndo_printf)(ndo, "\n\t");
			else
				(*ndo->ndo_printf)(ndo, " ");
			rip6_entry_print(ndo, re, 0);
			re++;
			length -= sizeof(*re);
		}
		break;

	case 2:
		/*
		 * RIPv2 response.
		 */
		i = length / sizeof(*re);
		if (i * sizeof(*re) == length)
			(*ndo->ndo_printf)(ndo, " ripng-resp %d:", i);
		else
			(*ndo->ndo_printf)(ndo, " ripng-resp %d[%u]:", i,
			    length + sizeof(*rp));
		re = (const struct rip6_entry *)dat;
		for (j = 0; j < i; j++) {
			if (ndo->ndo_vflag >= 2)
				(*ndo->ndo_printf)(ndo, "\n\t");
			else
				(*ndo->ndo_printf)(ndo, " ");
			rip6_entry_print(ndo, re, re->rip6_metric);
			re++;
			length -= sizeof(*re);
		}
		if (length)
			(*ndo->ndo_printf)(ndo, "[|ripng]");
		break;

	default:
		(*ndo->ndo_printf)(ndo, " ripng-%d ?? %u", rp->rip6_cmd,
		    length + sizeof(*rp));
		break;
	}
	if (rp->rip6_vers != 1)
		(*ndo->ndo_printf)(ndo, " [vers %d]", rp->rip6_vers);
}