void
eap_print(netdissect_options *ndo, const u_char *p, u_int length)
{
	const struct eap_frame_hdr *hdr;
	const u_char *cp;
	u_int subtype;
	u_int type;
	u_int tlen;
	u_char *tptr;
	int i;

	if (!((p) >= ndo->ndo_snapstart && (p) <= ndo->ndo_snapend - sizeof(struct eap_frame_hdr))) {
		(ndo)->ndo_printf((ndo), "\n\t[|EAP]");
		return;
	}

	hdr = (const struct eap_frame_hdr *)p;

	if (ndo->ndo_vflag > 0) {
		(ndo)->ndo_printf((ndo), "%s (%u) v%u, len %u",
		    tok2str(eap_frame_type_values, "unknown", hdr->eap_type),
		    hdr->eap_type, hdr->eap_version,
		    ((((u_int)(hdr->eap_len) & 0xff) << 8) | ((u_int)(hdr->eap_len) & 0xff00) >> 8));
	} else {
		(ndo)->ndo_printf((ndo), "%s (%u) v%u, len %u",
		    tok2str(eap_frame_type_values, "unknown", hdr->eap_type),
		    hdr->eap_type, hdr->eap_version, hdr->eap_len);
	}

	/*
	 * If it's an EAPOL frame, it has an 802.2 header we don't
	 * want to print.
	 */
	if (hdr->eap_type != 0)
		return;

	cp = (const u_char *)(hdr + 1);

	(ndo)->ndo_printf((ndo), ", %s (%u), id %u, len %u",
	    tok2str(eap_code_values, "unknown", *cp), *cp,
	    *(cp + 1), *(cp + 2));

	/*
	 * If the packet is truncated, just print the type and code.
	 */
	if (!((cp) >= ndo->ndo_snapstart && (cp) <= ndo->ndo_snapend - *(cp + 2))) {
		(ndo)->ndo_printf((ndo), "\n\t[|EAP]");
		return;
	}

	/*
	 * Don't go past the end of the captured data in the snapshot.
	 */
	if (ndo->ndo_snapend - cp < *(cp + 2))
		return;

	/*
	 * Most EAP methods are sent in the clear, so we don't bother
	 * decrypting them.  However, EAP-FAST and EAP-TTLS use
	 * encrypted tunnels, and EAP-TLS uses an encrypted tunnel
	 * for the actual authentication, so we decrypt those.
	 *
	 * EAP-FAST and EAP-TTLS use the same encrypted tunnel
	 * protocol, so we treat them the same way here.
	 */
	switch (*cp) {

	case 1: /* EAP_REQUEST */
	case 2: /* EAP_RESPONSE */
	case 3: /* EAP_SUCCESS */
	case 4: /* EAP_FAILURE */
		break;

	case 13: /* EAP_TLS */
	case 18: /* EAP_AKA */
	case 21: /* EAP_TTLS */
	case 43: /* EAP_FAST */
		break;

	default:
		return;
	}

	/*
	 * Skip the EAP header.
	 */
	cp += 5;

	switch (*cp) {

	case 1: /* EAP_TYPE_IDENTITY */
		cp++;
		tlen = *(cp - 1) - 5;
		if (tlen > 0) {
			(ndo)->ndo_printf((ndo), ", Identity: ");
			safeputs(ndo, cp, tlen);
		}
		break;

	case 2: /* EAP_TYPE_NOTIFICATION */
		cp++;
		tlen = *(cp - 1) - 5;
		if (tlen > 0) {
			(ndo)->ndo_printf((ndo), ", Notification: ");
			safeputs(ndo, cp, tlen);
		}
		break;

	case 3: /* EAP_TYPE_NAK */
		cp++;
		tlen = *(cp - 1) - 5;
		for (i = 0; i < tlen; i++) {
			(ndo)->ndo_printf((ndo), " %s (%u),",
			    tok2str(eap_type_values, "unknown", *cp),
			    *cp);
			cp++;
		}
		break;

	case 4: /* EAP_TYPE_MD5_CHALLENGE */
	case 5: /* EAP_TYPE_ONE_TIME_PASSWORD */
	case 6: /* EAP_TYPE_GENERIC_TOKEN_CARD */
		break;

	case 13: /* EAP_TYPE_TLS */
		(ndo)->ndo_printf((ndo), " flags [%s] 0x%02x,",
		    bittok2str(eap_tls_flags_values, "none", *(cp + 1)),
		    *(cp + 1));
		if ((*(cp + 1) & 0x80) != 0) {
			(ndo)->ndo_printf((ndo), " len %u",
			    ((((u_int)(*(cp + 2)) & 0xff) << 24) | (((u_int)(*(cp + 2 + 1)) & 0xff) << 16) | (((u_int)(*(cp + 2 + 2)) & 0xff) << 8) | ((u_int)(*(cp + 2 + 3)) & 0xff)));
		}
		break;

	case 18: /* EAP_TYPE_AKA */
		(ndo)->ndo_printf((ndo), " subtype [%s] 0x%02x,",
		    tok2str(eap_aka_subtype_values, "unknown", *cp),
		    *cp);
		break;

	case 21: /* EAP_TYPE_TTLS */
		(ndo)->ndo_printf((ndo), " TTLSv%u", *cp & 0x07);
		(ndo)->ndo_printf((ndo), " flags [%s] 0x%02x,",
		    bittok2str(eap_tls_flags_values, "none", *(cp + 1)),
		    *(cp + 1));
		if ((*(cp + 1) & 0x80) != 0) {
			(ndo)->ndo_printf((ndo), " len %u",
			    ((((u_int)(*(cp + 2)) & 0xff) << 24) | (((u_int)(*(cp + 2 + 1)) & 0xff) << 16) | (((u_int)(*(cp + 2 + 2)) & 0xff) << 8) | ((u_int)(*(cp + 2 + 3)) & 0xff)));
		}
		break;

	case 43: /* EAP_TYPE_FAST */
		(ndo)->ndo_printf((ndo), " FASTv%u", *cp & 0x07);
		(ndo)->ndo_printf((ndo), " flags [%s] 0x%02x,",
		    bittok2str(eap_tls_