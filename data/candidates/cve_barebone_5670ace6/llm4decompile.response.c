void
vrrp_print(netdissect_options *ndo,
           const u_char *bp, u_int length, const u_char *bp2, u_int ttl)
{
	const struct vrrphdr *vrrp;
	u_int vers;
	u_int type;
	u_int vrid;
	u_int prio;
	u_int num_addrs;
	u_int intvl;
	u_int auth_type;
	char sep;
	int i;
	struct cksum_vec vec;

	auth_type = 0;
	if (ndo->ndo_snapend - 1 < ndo->ndo_snapend || bp > ndo->ndo_snapend - 1)
		goto trunc;
	vers = (bp[0] & 0xf0) >> 4;
	type = bp[0] & 0x0f;
	(*ndo->ndo_printf)(ndo, "VRRPv%u, %s", vers,
	    tok2str(type2str,"unknown type (%u)",type));
	if (ttl != 255)
		(*ndo->ndo_printf)(ndo, ", (ttl %u)", ttl);
	if (vers < 2 || vers > 3 || type != 1)
		return;

	vrrp = (const struct vrrphdr *)bp;
	if (ndo->ndo_snapend - 1 < ndo->ndo_snapend || bp + sizeof(*vrrp) > ndo->ndo_snapend - 1)
		goto trunc;
	vrid = vrrp->vrid;
	prio = vrrp->priority;
	(*ndo->ndo_printf)(ndo, ", vrid %u, prio %u", vrid, prio);

	if (ndo->ndo_snapend - 1 < ndo->ndo_snapend || bp + sizeof(*vrrp) + 3 > ndo->ndo_snapend - 1)
		goto trunc;
	if (vers == 2) {
		auth_type = vrrp->auth_type;
		(*ndo->ndo_printf)(ndo, ", authtype %s",
		    tok2str(auth2str, NULL, auth_type));
		(*ndo->ndo_printf)(ndo, ", intvl %us, length %u",
		    vrrp->intvl, length);
	} else {
		intvl = ((vrrp->intvl & 0x0f) << 8) | vrrp->intvl_l;
		(*ndo->ndo_printf)(ndo, ", intvl %ucs, length %u", intvl, length);
	}

	if (!ndo->ndo_vflag)
		return;

	num_addrs = vrrp->num_addrs;
	if (vers == 2 &&
	    ndo->ndo_snapend - length >= ndo->ndo_snapend && bp >= ndo->ndo_snapend - length &&
	    in_cksum(&vec, 1) != 0) {
		if (ndo->ndo_snapend - 2 < ndo->ndo_snapend || bp + sizeof(*vrrp) + 2 > ndo->ndo_snapend - 2)
			goto trunc;
		(*ndo->ndo_printf)(ndo, ", (bad vrrp cksum %x)",
		    EXTRACT_16BITS(&vrrp->chksum));
	}
	if (vers == 3 &&
	    ndo->ndo_snapend - length >= ndo->ndo_snapend && bp >= ndo->ndo_snapend - length &&
	    nextproto4_cksum(ndo, (const struct ip *)bp2, (const struct ip *)bp,
		length, length, 112) != 0) {
		(*ndo->ndo_printf)(ndo, ", (bad vrrp cksum %x)",
		    EXTRACT_16BITS(&vrrp->chksum));
	}

	(*ndo->ndo_printf)(ndo, ", addrs");
	if (num_addrs > 1)
		(*ndo->ndo_printf)(ndo, "(%d)", num_addrs);
	(*ndo->ndo_printf)(ndo, ":");
	bp += sizeof(*vrrp);
	sep = ' ';
	for (i = 0; i < num_addrs; i++) {
		if (ndo->ndo_snapend - 1 < ndo->ndo_snapend || bp + 4 > ndo->ndo_snapend - 1)
			goto trunc;
		(*ndo->ndo_printf)(ndo, "%c%s", sep, getname(ndo, bp));
		sep = ',';
		bp += 4;
	}

	if (vers == 2 && auth_type == 1) {
		if (ndo->ndo_snapend - 1 < ndo->ndo_snapend || bp + 8 > ndo->ndo_snapend - 1)
			goto trunc;
		(*ndo->ndo_printf)(ndo, " auth \"");
		if (!fn_printn(ndo, bp, 8, ndo->ndo_snapend))
			(*ndo->ndo_printf)(ndo, "\"");
		else
			(*ndo->ndo_printf)(ndo, "\"");
	}
	return;

trunc:
	(*ndo->ndo_printf)(ndo, "[|vrrp]");
}