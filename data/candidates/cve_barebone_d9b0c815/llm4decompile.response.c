int
isis_print_extd_ip_reach(netdissect_options *ndo,
			 const u_char *bp, const char *ident, uint16_t afi)
{
	const u_char *cp;
	u_int processed;
	uint32_t metric;
	uint8_t prefix[16];
	u_int bit_length;
	u_int byte_length;
	u_int status_byte;
	u_int sublen;
	char ident_buffer[20];
	u_int subtlvtype;
	u_int subtlvlen;

	cp = bp;
	if (cp + 4 > ndo->ndo_snapend)
		return 0;
	metric = (*cp++ << 24) | (*cp++ << 16) | (*cp++ << 8) | *cp++;

	switch (afi) {
	case 2:
		if (cp + 1 > ndo->ndo_snapend)
			return 0;
		status_byte = *cp++;
		bit_length = status_byte & 0x3f;
		if (bit_length > 32) {
			(*ndo->ndo_printf)(ndo, "%sIPv4 prefix: bad bit length %u",
					   ident, bit_length);
			return 0;
		}
		processed = 5;
		break;
	case 10:
		if (cp + 2 > ndo->ndo_snapend)
			return 0;
		status_byte = *cp++;
		bit_length = *cp++;
		if (bit_length > 128) {
			(*ndo->ndo_printf)(ndo, "%sIPv6 prefix: bad bit length %u",
					   ident, bit_length);
			return 0;
		}
		processed = 6;
		break;
	default:
		return 0;
	}

	byte_length = (bit_length + 7) / 8;
	if (cp + byte_length > ndo->ndo_snapend)
		return 0;
	memset(prefix, 0, sizeof prefix);
	memcpy(prefix, cp, byte_length);
	cp += byte_length;
	processed += byte_length;

	switch (afi) {
	case 2:
		(*ndo->ndo_printf)(ndo, "%sIPv4 prefix: %15s/%u",
				   ident, ipaddr_string(ndo, prefix),
				   bit_length);
		break;
	case 10:
		(*ndo->ndo_printf)(ndo, "%sIPv6 prefix: %s/%u",
				   ident, ip6addr_string(ndo, prefix),
				   bit_length);
		break;
	}
	(*ndo->ndo_printf)(ndo, ", Distribution: %s, Metric: %u",
			   (status_byte & 0x80) ? "External" : "Internal",
			   metric);
	switch (afi) {
	case 2:
		if (status_byte & 0x40)
			(*ndo->ndo_printf)(ndo, ", sub-TLVs present");
		break;
	case 10:
		(*ndo->ndo_printf)(ndo, ", %s%s",
				   (status_byte & 0x40) ? "External" : "Internal",
				   (status_byte & 0x20) ? ", sub-TLVs present" : "");
		break;
	}

	switch (afi) {
	case 2:
		if (status_byte & 0x40)
			break;
		return processed;
	case 10:
		if (status_byte & 0x20)
			break;
		return processed;
	}

	if (cp + 1 > ndo->ndo_snapend)
		return 0;
	sublen = *cp++;
	processed++;
	(*ndo->ndo_printf)(ndo, " (%u)", sublen);
	while (sublen) {
		if (cp + 2 > ndo->ndo_snapend)
			return 0;
		subtlvtype = *cp++;
		subtlvlen = *cp++;
		snprintf(ident_buffer, sizeof ident_buffer, "%s  ", ident);
		if (!isis_print_ip_reach_subtlv(ndo, cp, subtlvtype, subtlvlen,
						ident_buffer))
			return 0;
		cp += subtlvlen;
		sublen -= subtlvlen + 2;
	}
	processed += sublen;
	return processed;
}