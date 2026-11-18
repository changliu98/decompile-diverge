void
print_attr_string(netdissect_options *ndo,
                  const u_char *data, u_int length, u_short attr_code)
{
	unsigned int i;
	const u_char *p;

	if (data > ndo->ndo_snapend - length ||
	    ndo->ndo_snapend - length < data) {
		(ndo)->ndo_printf((ndo), "%s", " [|radius]");
		return;
	}

	if (attr_code == 58) {
		(ndo)->ndo_printf((ndo), "%s (0x%02x) ", tok2str(rfc4675_tagged,"Unknown tag", *data), *data);
		data++;
		length--;
	} else if (attr_code == 66 || attr_code == 67) {
		if (*data > 31)
			goto trunc;
		if (length == 0) {
			(ndo)->ndo_printf((ndo), "%s", " [|radius]");
			return;
		}
		if (*data == 0)
			(ndo)->ndo_printf((ndo), "Tag[Unused] ");
		else
			(ndo)->ndo_printf((ndo), "Tag[%u] ", *data);
		data++;
		length--;
	} else if (attr_code == 81 || attr_code == 82 ||
		   attr_code == 84 || attr_code == 85) {
		if (*data > 31)
			goto trunc;
		if (length == 0) {
			(ndo)->ndo_printf((ndo), "%s", " [|radius]");
			return;
		}
		if (*data == 0)
			(ndo)->ndo_printf((ndo), "Tag[Unused] ");
		else
			(ndo)->ndo_printf((ndo), "Tag[%u] ", *data);
		data++;
		length--;
	} else if (attr_code == 69) {
		if (length < 3) {
			(ndo)->ndo_printf((ndo), "%s", " [|radius]");
			return;
		}
		if (*data == 0 || *data > 31)
			(ndo)->ndo_printf((ndo), "Tag[Unused] ");
		else
			(ndo)->ndo_printf((ndo), "Tag[%u] ", *data);
		(ndo)->ndo_printf((ndo), "Salt %u ", (data[1] << 8) | data[2]);
		data += 3;
		length -= 3;
	}

	p = data;
	for (i = 0; *p != '\0' && i < length; p++, i++) {
		(ndo)->ndo_printf((ndo), "%c", (*p >= 0x20 && *p <= 0x7e) ? *p : '.');
	}

trunc:
	return;
}