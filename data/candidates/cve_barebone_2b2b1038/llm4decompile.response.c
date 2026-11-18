void
vqp_print(netdissect_options *ndo, const u_char *cp, u_int length)
{
	const u_char *cp_orig = cp;
	const u_char *cp_next;
	unsigned int vqp_version;
	unsigned int vqp_msg_type;
	unsigned int vqp_error_code;
	unsigned int vqp_seq;
	unsigned int vqp_items;
	unsigned int vqp_obj_type;
	unsigned int vqp_obj_len;
	int tlen;

	/*
	 * This is a packet capture of a VQP message.  VQP is a
	 * Cisco-proprietary protocol used by some Cisco devices
	 * to communicate with the Cisco VQP daemon, which is
	 * running on the Cisco VQP server.
	 *
	 * VQP is a request/response protocol; a request sent by a
	 * Cisco device will elicit a response from the Cisco VQP
	 * server.
	 *
	 * VQP is a binary protocol; it has a header, which is
	 * followed by one or more TLVs.
	 *
	 * The header is 8 octets long, and has the following
	 * structure, with all values being big-endian:
	 *
	 * 0-1: version
	 *
	 *     The current version of VQP is 1.
	 *
	 * 2-3: message type
	 *
	 *     The message type is 1 for a request and 2 for a
	 *     response.
	 *
	 * 4-5: error code
	 *
	 *     The error code is 0 for "no error" for a request,
	 *     and is otherwise set to 0 for a response.
	 *
	 * 6-7: sequence number
	 *
	 *     The sequence number is set to 0 for a request, and
	 *     is set to the same value as the sequence number in
	 *     the header of the corresponding request for a
	 *     response.
	 *
	 * 8-9: number of items
	 *
	 *     The number of items is the number of TLVs in the
	 *     VQP message.
	 *
	 * The header is followed by one or more TLVs.  Each TLV
	 * has the following structure:
	 *
	 * 0-3: type
	 *
	 *     The type is a 32-bit value, with the high-order 16
	 *     bits being the enterprise number and the low-order
	 *     16 bits being the type within that enterprise.
	 *
	 *     Currently, the only enterprise number in use is
	 *     0x0c01, which is Cisco's enterprise number.
	 *
	 * 4-5: length
	 *
	 *     The length is a 16-bit value, giving the length, in
	 *     octets, of the value, following the length field,
	 *     in the TLV.
	 *
	 * 6-n: value
	 *
	 *     The value is the value of the TLV.
	 */

	/*
	 * Is there enough captured data for a VQP header?
	 */
	if (!((ndo)->ndo_snapend >= (const u_char *)(cp) && (const u_char *)(cp) >= (ndo)->ndo_snapend - (8))) {
		(ndo)->ndo_printf((ndo), "\n\t[|VQP]");
		return;
	}

	/*
	 * Get the version number.
	 */
	vqp_version = *cp++;

	/*
	 * Do we support this version?
	 */
	if (vqp_version != 1) {
		(ndo)->ndo_printf((ndo), "VQP version %u packet not supported", vqp_version);
		return;
	}

	/*
	 * Get the message type and error code.
	 */
	vqp_msg_type = *cp++;
	vqp_error_code = *cp++;

	/*
	 * If we're not printing verbosely, print a one-line summary.
	 */
	if (ndo->ndo_vflag < 1) {
		(ndo)->ndo_printf((ndo), "VQPv%u %s Message, error-code %s (%u), length %u",
		    vqp_version,
		    tok2str(vqp_msg_type_values, "unknown (%u)", vqp_msg_type),
		    tok2str(vqp_error_code_values, "unknown (%u)", vqp_error_code),
		    vqp_error_code, length);
		return;
	}

	/*
	 * Get the sequence number and number of items.
	 */
	vqp_seq = EXTRACT_32BITS(cp);
	cp += 4;
	vqp_items = *cp++;

	/*
	 * Print the VQP header.
	 */
	(ndo)->ndo_printf((ndo), "\n\tVQPv%u, %s Message, error-code %s (%u), seq 0x%08x, items %u, length %u",
	    vqp_version,
	    tok2str(vqp_msg_type_values, "unknown (%u)", vqp_msg_type),
	    tok2str(vqp_error_code_values, "unknown (%u)", vqp_error_code),
	    vqp_error_code, vqp_seq, vqp_items, length);

	/*
	 * Loop through the items.
	 */
	tlen = length - 8;
	while (vqp_items != 0 && tlen > 0) {
		/*
		 * Is there enough captured data for this TLV?
		 */
		if (!((ndo)->ndo_snapend >= (const u_char *)(cp) && (const u_char *)(cp) >= (ndo)->ndo_snapend - (6))) {
			(ndo)->ndo_printf((ndo), "\n\t[|VQP]");
			return;
		}

		/*
		 * Get the type and length.
		 */
		vqp_obj_tlv = (vqp_obj_tlv_t *)cp;
		vqp_obj_type = EXTRACT_32BITS(&vqp_obj_tlv->type);
		vqp_obj_len = EXTRACT_16BITS(&vqp_obj_tlv->len);

		/*
		 * Print the type and length.
		 */
		(ndo)->ndo_printf((ndo), "\n\t  %s Object (0x%08x), length %u, value: ",
		    tok2str(vqp_obj_values, "Unknown", vqp_obj_type),
		    vqp_obj_type, vqp_obj_len);

		/*
		 * If there's no type or length, we're done.
		 */
		if (vqp_obj_type == 0 || vqp_obj_len == 0)
			return;

		/*
		 * Is there enough captured data for this TLV's value?
		 */
		cp_next = cp + 6 + vqp_obj_len;
		if (!((ndo)->ndo_snapend >= (const u_char *)(cp) && (const u_char *)(cp) >= (ndo)->ndo_snapend - (vqp_obj_len))) {
			(ndo)->ndo_printf((ndo), "\n\t[|VQP]");
			return;
		}

		/*
		 * Print the value, if we're printing at verbosity level 2
		 * or higher.
		 */
		if (ndo->ndo_vflag >= 2) {
			switch (vqp_obj_type) {

			case 0x0c010001:
			case 0x0c010002:
			case 0x0c010003