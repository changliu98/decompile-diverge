u_int
ieee802_11_print(netdissect_options *ndo, const u_char *p, u_int length, u_int caplen,
    int pad, u_int fcslen)
{
	u_int orig_length = length;
	u_int hdrlen;
	u_int meshdrlen;
	u_int llc_hdrlen;
	u_int fclen;
	u_short fc;
	const struct ieee802_11_hdr *hdr;
	lladdr_info src, dst;

	if (length < fcslen) {
		ndo->ndo_printf(ndo, "%s", "[|802.11]");
		return (length);
	}
	length -= fcslen;
	fclen = fcslen;

	/*
	 * XXX
	 *
	 * Some 802.11 captures have the 802.11 header *and* the LLC
	 * header.  Some don't.  Some have padding between the 802.11
	 * header and the LLC header.  Some have the 802.11 header,
	 * followed by the LLC header and then data, with no padding.
	 * Some have the 802.11 header, a padding byte, and then the
	 * start of the LLC header.
	 *
	 * If we have a 802.11 header with no padding, and a LLC
	 * header, and the "protocol type" field in the LLC header
	 * is one of the "control protocol types" (LLC XID response,
	 * LLC XID update request, or LLC XID update response),
	 * and the DSAP is the IEEE 802.2 DSAP for the 802.11
	 * "Logical Link Control" protocol, and the SSAP is the
	 * IEEE 802.2 SSAP for the 802.11 "Logical Link Control"
	 * protocol, then the packet is an 802.11 packet with no
	 * padding.
	 *
	 * Otherwise, if the packet is an 802.11 packet with no
	 * padding, and the "protocol type" field in the LLC
	 * header is not one of the "control protocol types",
	 * and the DSAP is the IEEE 802.2 DSAP for the 802.11
	 * "Logical Link Control" protocol, and the SSAP is the
	 * IEEE 802.2 SSAP for the 802.11 "Logical Link Control"
	 * protocol, then the packet is an 802.11 packet with
	 * a padding byte.
	 *
	 * Otherwise, the packet is not an 802.11 packet.
	 *
	 * (This is all a consequence of the fact that the 802.11
	 * "Logical Link Control" protocol is just the IEEE 802.2
	 * Logical Link Control protocol, with a DSAP of 0xaa
	 * and an SSAP of 0xaa.)
	 *
	 * (This is all pretty much independent of byte-swapping
	 * issues, by the way.)
	 */

	/*
	 * Has "802.11" header.
	 */
	if (caplen < 2) {
		/*
		 * XXX - this "can't happen" because "ieee802_11_ifprint()"
		 * checks for a minimum packet length and rejects packets
		 * that are too short.
		 */
		ndo->ndo_printf(ndo, "%s", "[|802.11]");
		return (caplen);
	}

	hdr = (const struct ieee802_11_hdr *)p;
	fc = hdr->frame_control;

	hdrlen = extract_header_length(ndo, fc);
	if (hdrlen == 0)
		return (0);

	if (pad)
		hdrlen = (hdrlen + 3) & ~3;

	if (ndo->ndo_Hflag &&
	    (((fc & IEEE802_11_FC_TYPE_MASK) >> 2) == 2) &&
	    (fc & IEEE802_11_FC_ORDER)) {
		/*
		 * Mesh point
		 */
		meshdrlen = extract_mesh_header_length(p + hdrlen);
		hdrlen += meshdrlen;
	} else
		meshdrlen = 0;

	if (caplen < hdrlen) {
		/*
		 * XXX - this "can't happen" because "ieee802_11_ifprint()"
		 * checks for a minimum packet length and rejects packets
		 * that are too short.
		 */
		ndo->ndo_printf(ndo, "%s", "[|802.11]");
		return (hdrlen);
	}

	if (ndo->ndo_eflag)
		ieee_802_11_hdr_print(ndo, fc, p, hdrlen, meshdrlen);

	p += hdrlen;
	length -= hdrlen;
	caplen -= hdrlen;

	src.addr_string = etheraddr_string;
	dst.addr_string = etheraddr_string;

	switch ((fc & IEEE802_11_FC_TYPE_MASK) >> 2) {

	case 0:
		/*
		 * Management frame.
		 */
		get_mgmt_src_dst_mac(p - hdrlen, &src.addr, &dst.addr);
		if (!mgmt_body_print(ndo, fc, src.addr, p, length)) {
			ndo->ndo_printf(ndo, "%s", "[|802.11]");
			return (hdrlen);
		}
		break;

	case 1:
		/*
		 * Control frame.
		 */
		if (!ctrl_body_print(ndo, fc, p - hdrlen)) {
			ndo->ndo_printf(ndo, "%s", "[|802.11]");
			return (hdrlen);
		}
		break;

	case 2:
		/*
		 * Data frame.
		 */
		if (fc & IEEE802_11_FC_SUBTYPE_NULL) {
			/*
			 * "Null" data packet.
			 */
			return (hdrlen);
		}

		if (fc & IEEE802_11_FC_WEP) {
			/*
			 * WEP-encrypted packet.
			 */
			ndo->ndo_printf(ndo, "Data");
			if (!wep_print(ndo, p)) {
				ndo->ndo_printf(ndo, "%s", "[|802.11]");
				return (hdrlen);
			}
			break;
		}

		/*
		 * Normal data packet.
		 */
		get_data_src_dst_mac(fc, p - hdrlen, &src.addr, &dst.addr);
		llc_hdrlen = llc_print(ndo, p, length, caplen, &src, &dst);
		if (llc_hdrlen < 0) {
			/*
			 * Some kinds of LLC packet we cannot
			 * handle intelligently
			 */
			if (!ndo->ndo_suppress_default_print)
				ndo->ndo_default_print(ndo, p, caplen);
			llc_hdrlen = -llc_hdrlen;
		}
		hdrlen += llc_hdrlen;
		break;

	default:
		/*
		 * Some kind of packet we don't know how to
		 * handle intelligently
		 */
		nd