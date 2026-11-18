void
bgp_capabilities_print(netdissect_options *ndo, const u_char *opt, u_int caps_len)
{
	int i;
	u_int cap_type;
	u_int cap_len;
	const char *cap_name;

	for (i = 0; i < caps_len; i += cap_len + 2) {
		/*
		 * XXX - this should really use a "capability" structure,
		 * with a "print" member that's a routine that takes
		 * an "ndo" and a "capability" structure and prints it.
		 *
		 * The "print" routine would first check the capability
		 * length against the minimum length for the capability
		 * type, and report an error if it's too short.
		 *
		 * The "print" routine would also check the capability
		 * type against a table of known capability types,
		 * reporting an error if the type is unknown.
		 *
		 * The "print" routine would then print the capability
		 * using the ndo.
		 *
		 * The "print" routine would return the number of bytes
		 * it used, so that the caller could check that it
		 * consumed the entire capability.
		 *
		 * The "print" routine would register itself with the
		 * "capability" structure, using the capability type
		 * as the index into the table of "print" routines.
		 *
		 * The "print" routine would be passed the "capability"
		 * structure, which would include the capability type
		 * and the capability length, and a pointer to the
		 * capability data.
		 *
		 * The "print" routine would be passed the "ndo", so
		 * it could use the ndo to print the capability.
		 *
		 * The "print" routine would use the "print_unknown_data()"
		 * routine, passing it the "ndo", a pointer to the
		 * capability data, and the capability length, to
		 * print the capability if the "verbose" flag is set
		 * to 2 or more.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "no decoder for Capability %u",
		 * passing it the capability type, if the "verbose"
		 * flag is set to 1 or less.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * length is 0.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * type is unknown.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * length is too short.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * type is unknown.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * length is too short.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * type is unknown.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * length is too short.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * type is unknown.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * length is too short.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * type is unknown.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * length is too short.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * type is unknown.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * length is too short.
		 *
		 * The "print" routine would use the "ndo" to print
		 * a message saying "[|BGP]", if the capability
		 * type is unknown.
		 *
		 * The "print void
bgp_capabilities_print(netdissect_options *ndo, const u_char *opt, u_int caps_len)
{
	int j;
	u_int cap_offset;
	u_int tcap_len;

	for (j = 0; j < caps_len; j += cap_len + 2) {
		if (&opt[j + 1] > ndo->ndo_snapend - 2 ||
		    &opt[j + 1] < ndo->ndo_snapend - 2) {
			(*ndo->ndo_printf)(ndo, "[|BGP]");
			return;
		}
		cap_type = opt[j];
		cap_len = opt[j + 1];
		(*ndo->ndo_printf)(ndo, "\n\t      %s (%u), length: %u",
		    tok2str(bgp_capcode_values,"Unknown",cap_type),
		    cap_type, cap_len);
		if (&opt[j + cap_len] > ndo->ndo_snapend - cap_len ||
		    &opt[j + cap_len] < ndo->ndo_snapend - cap_len) {
			(*ndo->ndo_printf)(ndo, "[|BGP]");
			return;
		}
		switch (cap_type) {

		case 1:
			(*ndo->ndo_printf)(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u)",
			    tok2str(af_values,"Unknown",EXTRACT_16BITS(&opt[j+2])),
			    EXTRACT_16BITS(&opt[j+2]),
			    tok2str(bgp_safi_values,"Unknown",opt[j+5]),
			    opt[j+5]);
			break;

		case 2:
			/*
			 * This is obsolete and should never be sent.
			 */
			break;

		case 64:
			(*ndo->ndo_printf)(ndo, "\n\t\tRestart Flags: [%s], Restart Time %us",
			    (opt[j+2] & 0x80) ? "R" : "",
			    EXTRACT_16BITS(&opt[j+2]) & 0x0fff);
			cap_offset = 4;
			tcap_len = cap_len - 2;
			while (tcap_len >= 4) {
				(*ndo->ndo_printf)(ndo,
				"\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",
				    tok2str(af_values,"Unknown",EXTRACT_16BITS(&opt[j+cap_offset])),
				    EXTRACT_16BITS(&opt[j+cap_offset]),
				    tok2str(bgp_safi_values,"Unknown",opt[j+cap_offset+