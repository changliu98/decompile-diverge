int
rpki_rtr_pdu_print(netdissect_options *ndo, const u_char *cp, u_int indent)
{
	u_int pdu_type;
	u_int pdu_length;
	u_int unknown_flag;
	const u_char *pdu_start;
	const u_char *pdu_end;
	const u_char *pdu_next;
	u_int pdu_next_length;
	u_int pdu_remaining_length;
	u_int error_code;
	u_int encapsulated_pdu_length;
	u_int text_length;
	u_int origin_as;
	u_int prefix_length_min;
	u_int prefix_length_max;
	u_int flags;
	u_int session_id;
	u_int serial;
	u_int hexdump;

	pdu_start = cp;
	pdu_type = cp[1];
	pdu_length = (cp[4] << 24) | (cp[5] << 16) | (cp[6] << 8) | cp[7];
	pdu_end = pdu_start + pdu_length;
	if (pdu_end > ndo->ndo_snapend || pdu_start > ndo->ndo_snapend - pdu_length)
		return (1);

	unknown_flag = 0;
	ndo->ndo_printf(ndo, "%sRPKI-RTRv%u, %s PDU (%u), length: %u",
	    indent_string(8), cp[0],
	    tok2str(rpki_rtr_pdu_values, "Unknown", pdu_type), pdu_type,
	    pdu_length);

	switch (pdu_type) {
	case 0: /* RPKI-RTR PDU IPv4 */
		pdu_next = cp + 8;
		session_id = (cp[2] << 8) | cp[3];
		serial = (cp[8] << 24) | (cp[9] << 16) | (cp[10] << 8) | cp[11];
		ndo->ndo_printf(ndo, "%sSession ID: 0x%04x, Serial: %u",
		    indent_string(indent + 2), session_id, serial);
		break;
	case 1: /* RPKI-RTR PDU IPv6 */
		pdu_next = cp + 8;
		session_id = (cp[2] << 8) | cp[3];
		serial = (cp[8] << 24) | (cp[9] << 16) | (cp[10] << 8) | cp[11];
		ndo->ndo_printf(ndo, "%sSession ID: 0x%04x, Serial: %u",
		    indent_string(indent + 2), session_id, serial);
		break;
	case 2: /* RPKI-RTR PDU End-of-Data */
		pdu_next = cp + 8;
		break;
	case 3: /* RPKI-RTR PDU Keep-Alive */
		pdu_next = cp + 8;
		session_id = (cp[2] << 8) | cp[3];
		ndo->ndo_printf(ndo, "%sSession ID: 0x%04x",
		    indent_string(indent + 2), session_id);
		break;
	case 4: /* RPKI-RTR PDU IPv4 Prefix */
		pdu_next = cp + 8;
		prefix_length_min = cp[9];
		prefix_length_max = cp[10];
		origin_as = (cp[16] << 24) | (cp[17] << 16) |
		    (cp[18] << 8) | cp[19];
		flags = cp[8];