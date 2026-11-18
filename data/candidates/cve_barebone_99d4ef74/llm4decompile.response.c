int
lldp_mgmt_addr_tlv_print(netdissect_options *ndo, const u_char *tlv, u_int length)
{
	const u_char *p;
	u_int subtype;
	u_int intf_num;
	u_int oid_len;
	u_int addr_len;
	const char *addr_str;

	if (length == 0)
		return 0;

	addr_len = *tlv;
	if (length - 1 < addr_len)
		return 0;

	p = tlv + 1;
	length -= 1;

	addr_str = lldp_network_addr_print(ndo, p, addr_len);
	if (addr_str == NULL)
		return 0;
	(*ndo->ndo_printf)(ndo, "\n\t  Management Address length %u, %s", addr_len, addr_str);

	p += addr_len;
	length -= addr_len;

	if (length < 5)
		return 0;

	subtype = *p++;
	(*ndo->ndo_printf)(ndo, "\n\t  %s Interface Numbering (%u): %u",
	    tok2str(lldp_intf_numb_subtype_values, "Unknown", subtype),
	    subtype,
	    (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);

	p += 4;
	length -= 4;

	if (length == 0)
		return 1;

	oid_len = *p++;
	if (length - 1 < oid_len)
		return 0;

	if (oid_len) {
		(*ndo->ndo_printf)(ndo, "\n\t  OID length %u", oid_len);
		safeputs(ndo, p, oid_len);
	}

	return 1;
}