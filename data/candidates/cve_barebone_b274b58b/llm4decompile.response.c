u_int
mfr_print(netdissect_options *ndo, const u_char *p, u_int length)
{
	const u_char *cp;
	u_int caplen = ndo->ndo_snapend - p;
	u_int hdrlen;
	u_int ielen;
	u_int msg_type;
	u_int seq_num;
	u_int flags;

	/*
	 * This is a "bare" 802.11 frame, with no 802.11 header
	 * (management frame or data frame with data part
	 * encrypted).
	 *
	 * The first two bytes are a "frame control" field, which
	 * includes bits for the frame type, flags, and other stuff.
	 *
	 * The rest of the frame is fragmented data and flags.
	 */

	/*
	 * The first two bytes are a "frame control" field, which
	 * includes bits for the frame type, flags, and other stuff.
	 */
	if (caplen < 2)
		goto trunc;
	flags = p[0];
	msg_type = p[1];

	/*
	 * If the "type" is zero, this is a "control" message.
	 * The message type is actually in the third byte.
	 */
	if ((flags & 0xe0) == 0xe0 && msg_type == 0) {
		cp = p + 2;
		hdrlen = 3;
		msg_type = *cp;
		ndo->ndo_printf(ndo, "FRF.16 Control, Flags [%s], %s, length %u",
		    bittok2str(frf_flag_values, "none", flags & 0xe0),
		    tok2str(mfr_ctrl_msg_values,
		    "Unknown Message (0x%02x)", msg_type),
		    length);
		if (ndo->ndo_vflag == 0)
			return (hdrlen);
		goto print_ies;
	}

	/*
	 * This is a fragment.
	 */
	seq_num = ((flags & 0x1e) << 7) | msg_type;
	if ((flags & 0xe0) == 0xc0 || (flags & 0xe0) == 0x80) {
		/*
		 * This is a data fragment.
		 */
		cp = p + 2;
		hdrlen = 2;
		ndo->ndo_printf(ndo, "FRF.16 Frag, seq %u, Flags [%s], ",
		    seq_num,
		    bittok2str(frf_flag_values, "none", flags & 0xe0));
		fr_print(ndo, cp, length - hdrlen);
	} else {
		/*
		 * This is a control fragment.
		 */
		cp = p;
		hdrlen = 0;
		ndo->ndo_printf(ndo, "FRF.16 Frag, seq %u, Flags [%s]",
		    seq_num,
		    bittok2str(frf_flag_values, "none", flags & 0xe0));
		print_unknown_data(ndo, cp, "\n\t", length);
	}
	return (hdrlen);

trunc:
	ndo->ndo_printf(ndo, "[|mfr]");
	return (length);

print_ies:
	/*
	 * Print any Information Elements.
	 */
	length -= hdrlen;
	while (length >= 2) {
		if (caplen < 2)
			goto trunc;
		ie_type = *cp++;
		ielen = *cp++;
		length -= 2;
		ndo->ndo_printf(ndo, "\n\tIE %s (%u), length %u: ",
		    tok2str(mfr_ctrl_ie_values, "Unknown", ie_type),
		    ie_type, ielen);
		if (ielen == 0 || ie_type == 0)
			break;
		if (caplen < ielen)
			goto trunc;
		caplen -= ielen;
		switch (ie_type) {

		case 1: /* MFR_IE_STATION_ID */
		case 2: /* MFR_IE_SERVICE_SET_ID */
			{
				u_int i;

				for (i = 0; i < ielen && i < 50; i++) {
					if (cp[i] == '\0')
						break;
					safeputchar(ndo, cp[i]);
				}
			}
			break;

		case 3: /* MFR_IE_MFR_CAPABILITY */
			ndo->ndo_printf(ndo, "0x%08x", EXTRACT_32BITS(cp));
			break;

		case 5: /* MFR_IE_TIMESTAMP */
			if (ielen == 16)
				ts_print(ndo, cp);
			break;

		case 6: /* MFR_IE_CHALLENGE */
		case 7: /* MFR_IE_RESPONSE */
		default:
			break;
		}
		if (ndo->ndo_vflag >= 2)
			print_unknown_data(ndo, cp, "\n\t  ", ielen);
		cp += ielen;
		length -= ielen;
	}
	return (hdrlen);
}