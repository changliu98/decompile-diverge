void
arp_print(netdissect_options *ndo,
          const u_char *p, u_int length, u_int caplen)
{
	u_short hrd, pro, op;
	int hext = 0;
	const char *opstr;
	const char *hard, *proto;
	const u_char *sender_hw, *sender_ip, *target_hw, *target_ip;
	u_int sender_hw_len, sender_ip_len, target_hw_len, target_ip_len;
	int linkaddr;

	if (!((ndo)->ndo_snapend >= (p) && (p) >= (ndo)->ndo_snapend - 8)) {
		(ndo)->ndo_printf((ndo), "%s", "[|ARP]");
		return;
	}

	hrd = EXTRACT_16BITS(p);
	pro = EXTRACT_16BITS(p + 2);
	op = EXTRACT_16BITS(p + 4);

	linkaddr = (hrd == 15);

	/*
	 * XXX - this is a hack till I work out how to parse the rest
	 * of the ARP protocols
	 */
	if (hrd == 19) {
		atmarp_print(ndo, p, length, caplen);
		return;
	}

	/*
	 * If the packet is shorter than the ARP header, or if the
	 * hardware address length field is longer than the packet,
	 * this isn't an ARP packet.
	 */
	if (p[5] == 0 || !((ndo)->ndo_snapend >= (p) && (p) >= (ndo)->ndo_snapend - (p[5])) ||
	    !((ndo)->ndo_snapend >= (p + 8 + (p[4] << 1) + p[5]) && (p + 8 + (p[4] << 1) + p[5]) >= (p) + 8)) {
		(ndo)->ndo_printf((ndo), "%s", "[|ARP]");
		(ndo)->ndo_default_print((ndo), p, length);
		return;
	}

	if (!ndo->ndo_eflag)
		(ndo)->ndo_printf((ndo), "ARP, ");

	/*
	 * If the protocol is IPv4 or IPv6, give the packet to
	 * ip_print() to print.
	 */
	if ((pro == 0x0800 || pro == 0x1000) &&
	    p[5] == sizeof(u_int32_t) &&
	    p[4] != 0 &&
	    !ndo->ndo_vflag) {
		(ndo)->ndo_default_print((ndo), p, length);
		return;
	}

	hard = tok2str(arphrd_values, "Unknown Hardware (%u)", hrd);
	proto = tok2str(ethertype_values, "Unknown Protocol (0x%04x)", pro);

	(ndo)->ndo_printf((ndo), "%s (len %u), %s (len %u)", hard, p[4], proto, p[5]);

	if (ndo->ndo_vflag) {
		opstr = tok2str(arpop_values, "Unknown (%u)", op);
		(ndo)->ndo_printf((ndo), "%s%s ", ndo->ndo_vflag ? ", " : "", opstr);
	}

	switch (op) {

	case 1:				/* ARP request */
		sender_hw = p + 8;
		sender_hw_len = p[4];
		sender_ip = p + 8 + p[4];
		sender_ip_len = p[5];
		target_hw = p + 8 + p[4] + p[5];
		target_hw_len = p[4];
		target_ip = p + 8 + (p[4] << 1) + p[5];
		target_ip_len = p[5];

		(ndo)->ndo_printf((ndo), "who-has %s", getname(ndo, target_ip));
		if (isnonzero(sender_hw, sender_hw_len))
			(ndo)->ndo_printf((ndo), " (%s)", linkaddr_string(ndo, sender_hw, linkaddr, sender_hw_len));
		(ndo)->ndo_printf((ndo), " tell %s", getname(ndo, sender_ip));
		break;

	case 2:				/* ARP reply */
		sender_hw = p + 8;
		sender_hw_len = p[4];
		sender_ip = p + 8 + p[4];
		sender_ip_len = p[5];
		target_hw = p + 8 + p[4] + p[5];
		target_hw_len = p[4];
		target_ip = p + 8 + (p[4] << 1) + p[5];
		target_ip_len = p[5];

		(ndo)->ndo_printf((ndo), "%s is-at %s", getname(ndo, sender_ip),
		    linkaddr_string(ndo, sender_hw, linkaddr, sender_hw_len));
		break;

	case 3:				/* RARP request */
		sender_hw = p + 8;
		sender_hw_len = p[4];
		sender_ip = p + 8 + p[4];
		sender_ip_len = p[5];
		target_hw = p + 8 + p[4] + p[5];
		target_hw_len = p[4];
		target_ip = p + 8 + (p[4] << 1) + p[5];
		target_ip_len = p[5];

		(ndo)->ndo_printf((ndo), "who-is %s tell %s",
		    linkaddr_string(ndo, target_hw, linkaddr, target_hw_len),
		    linkaddr_string(ndo, sender_hw, linkaddr, sender_hw_len));
		break;

	case 4:				/* RARP reply */
		sender_hw = p + 8;
		sender_hw_len = p[4];
		sender_ip = p + 8 + p[4];
		sender_ip_len = p[5];
		target_hw = p + 8 + p[4] + p[5];
		target_hw_len = p[4];
		target_ip = p + 8 + (p[4] << 1) + p[5];
		target_ip_len = p[5];

		(ndo)->ndo_printf((ndo), "%s at %s",
		    linkaddr_string(ndo, target_hw, linkaddr, target_hw_len),
		    getname(ndo, target_ip));
		break;

	case 8:				/* Inverse ARP request */
		sender_hw = p + 8;
		sender_hw_len = p[4];
		sender_ip = p + 8 + p[4];
		sender_ip_len = p[5];
		target_hw = p + 8 + p[4] + p[5];
		target_hw_len = p[4];
		target_ip = p + 8 + (p[4] << 1) + p[5];
		target_ip_len = p[5];

		(ndo)->ndo_printf((ndo), "who-is %s tell %s",
		    linkaddr_string(ndo, target_hw, linkaddr, target_hw_len),
		    linkaddr_string(ndo, sender_hw, linkaddr, sender_hw_len));
		break;

	case 9: