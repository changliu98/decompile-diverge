void
bgp_capabilities_print(netdissect_options *ndo, const u_char *opt, u_int caps_len)
{
	u_int i;
	u_char cap_type;
	u_char cap_len;
	u_int asn;

	for (i = 0; i < caps_len; ) {
		if (&opt[i] > ndo->ndo_snapend - 2)
			goto trunc;
		cap_type = opt[i];
		cap_len = opt[i+1];
		ndo->ndo_printf(ndo, "\n\t      %s (%u), length: %u",
		    tok2str(bgp_capcode_values,"Unknown",cap_type),
		    cap_type, cap_len);
		if (&opt[i+2] > ndo->ndo_snapend - cap_len)
			goto trunc;
		switch (cap_type) {

		case 1: /* Multiprotocol Extensions */
			ndo->ndo_printf(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u)",
			    tok2str(af_values,"Unknown",(opt[i+2]<<8)|opt[i+3]),
			    (opt[i+2]<<8)|opt[i+3],
			    tok2str(bgp_safi_values,"Unknown",opt[i+5]),
			    opt[i+5]);
			break;

		case 2: /* Route Refresh Capability */
			/* No parameters. */
			break;

		case 64: /* BGP-4 Restart */
			if (&opt[i+2] > ndo->ndo_snapend - 2)
				goto trunc;
			ndo->ndo_printf(ndo, "\n\t\tRestart Flags: [%s], Restart Time %us",
			    (opt[i+2] & 0x80) ? "R" : "",
			    (opt[i+2]<<8 | opt[i+3]) & 0x0fff);
			cap_len -= 2;
			for (cap_type = 4; cap_len >= 4; cap_len -= 4) {
				ndo->ndo_printf(ndo,
				    "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",
				    tok2str(af_values,"Unknown",(opt[i+cap_type]<<8)|opt[i+cap_type+1]),
				    (opt[i+cap_type]<<8)|opt[i+cap_type+1],
				    tok2str(bgp_safi_values,"Unknown",opt[i+cap_type+2]),
				    opt[i+cap_type+2],
				    (opt[i+cap_type+3] & 0x80) ? "Yes" : "No");
				cap_type += 4;
			}
			break;

		case 65: /* BGP-4 AS4 */
			if (cap_len == 4) {
				asn = (opt[i+2]<<24) | (opt[i+3]<<16) |
				      (opt[i+4]<<8) | (opt[i+5]);
				ndo->ndo_printf(ndo, "\n\t\t 4 Byte AS %s",
				    as_printf(ndo, astostr, 20, asn));
			}
			break;

		case 69: /* BGP-4 Add-Path */
			cap_type = 2;
			cap_len -= 2;
			if (cap_len == 0)