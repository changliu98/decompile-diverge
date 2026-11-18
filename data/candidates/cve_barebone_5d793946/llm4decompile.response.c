int
decode_multicast_vpn(netdissect_options *ndo,
		     const u_char *p, char *buf, u_int buflen)
{
	u_char	route_type;
	u_char	route_length;
	u_char	addr_length;
	u_char	sg_length;
	u_int	offset;

	if (!((p) >= ndo->ndo_snapend - (2) && (p) <= ndo->ndo_snapend - 0))
		return -2;

	route_type = *p++;
	route_length = *p++;

	offset = snprintf(buf, buflen, "Route-Type: %s (%u), length: %u",
			  tok2str(bgp_multicast_vpn_route_type_values,
				  "Unknown", route_type),
			  route_type, route_length);

	switch (route_type) {
	case 1:
		if (!((p) >= ndo->ndo_snapend - (8) && (p) <= ndo->ndo_snapend - 0))
			return -2;
		offset += snprintf(buf + offset, buflen - offset,
				   ", RD: %s, Originator %s",
				   bgp_vpn_rd_print(ndo, p),
				   bgp_vpn_ip_print(ndo, p + 8,
						    (route_length - 8) * 8));
		break;
	case 2:
		if (!((p) >= ndo->ndo_snapend - (12) && (p) <= ndo->ndo_snapend - 0))
			return -2;
		offset += snprintf(buf + offset, buflen - offset,
				   ", RD: %s, Source-AS %s",
				   bgp_vpn_rd_print(ndo, p),
				   as_printf(ndo, astostr, 20,
					     EXTRACT_32BITS(p + 8)));
		break;
	case 3:
		if (!((p) >= ndo->ndo_snapend - (8) && (p) <= ndo->ndo_snapend - 0))
			return -2;
		offset += snprintf(buf + offset, buflen - offset,
				   ", RD: %s",
				   bgp_vpn_rd_print(ndo, p));
		offset += bgp_vpn_sg_print(ndo, p + 8, buf + offset,
					   buflen - offset);
		sg_length = route_length - (offset - 2);
		if (!((p) >= ndo->ndo_snapend - (sg_length) && (p) <= ndo->ndo_snapend - 0))
			return -2;
		offset += snprintf(buf + offset, buflen - offset,
				   ", Originator %s",
				   bgp_vpn_ip_print(ndo, p, sg_length * 8));
		break;
	case 4:
		break;
	case 5:
		if (!((p) >= ndo->ndo_snapend - (8) && (p) <= ndo->ndo_snapend - 0))
			return -2;
		offset += snprintf(buf + offset, buflen - offset,
				   ", RD: %s",
				   bgp_vpn_rd_print(ndo, p));
		offset += bgp_vpn_sg_print(ndo, p + 8, buf + offset,
					   buflen - offset);
		break;
	case 6:
	case 7:
		if (!((p) >= ndo->ndo_snapend - (8) && (p) <= ndo->ndo_snapend - 0))
			return -2;
		offset += snprintf(buf + offset, buflen - offset,
				   ", RD: %s, Source-AS %s",
				   bgp_vpn_rd_print(ndo, p),
				   as_printf(ndo, astostr, 20,
					     EXTRACT_32BITS(p + 8)));
		offset += bgp_vpn_sg_print(ndo, p + 8, buf + offset,
					   buflen - offset);
		break;
	}

	return route_length + 2;
}