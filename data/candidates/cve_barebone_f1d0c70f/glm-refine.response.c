void __cdecl ip_optprint(netdissect_options *ndo, const u_char *cp, u_int length)
{
    const char *sep = "";

    while (length)
    {
        ndo->ndo_printf(ndo, "%s", sep);
        sep = ",";

        // Check if at least 1 byte is available for the option code
        if (!ND_BYTES_ARE_SAFELY_AVAILABLE(ndo, cp, 1))
            goto trunc;

        uint8_t option_code = *cp;
        const char *option_str = tok2str(&ip_option_values, "unknown %u", option_code);
        ndo->ndo_printf(ndo, "%s", option_str);

        uint32_t option_len;

        if (option_code > 1)
        {
            // Check if at least 2 bytes are available to read the length field
            if (!ND_BYTES_ARE_SAFELY_AVAILABLE(ndo, cp, 2))
                goto trunc;

            option_len = cp[1];
            if (option_len < 2)
                goto bad_len;
        }
        else
        {
            // Options 0 (End of Options) and 1 (No Operation) have an implicit length of 1
            option_len = 1;
        }

        if (option_len > length)
            goto bad_len;

        // Check if the full option length is safely available in the buffer
        if (!ND_BYTES_ARE_SAFELY_AVAILABLE(ndo, cp, option_len))
            goto trunc;

        // Option code 0: End of Options List
        if (!option_code)
            return;

        // Option code 1: No Operation
        if (option_code != 1)
        {
            switch (option_code)
            {
                case 7:   // Record Route
                case 0x83: // Loose Source Route
                case 0x89: // Strict Source Route
                    ip_printroute(ndo, cp, option_len);
                    break;

                case 0x44: // Internet Timestamp
                    ip_printts(ndo, cp, option_len);
                    break;

                case 0x82: // Traceroute
                    break;

                case 0x94: // Router Alert
                    if (option_len >= 4)
                    {
                        // Check if 4 bytes are safely available
                        if (!ND_BYTES_ARE_SAFELY_AVAILABLE(ndo, cp, 4))
                            goto trunc;

                        // cp + 1 skips the option type and length bytes, pointing to the 2-byte value
                        uint16_t router_alert_value = _byteswap_ushort(*(uint16_t *)(cp + 2));
                        if (router_alert_value)
                            ndo->ndo_printf(ndo, " value %u", router_alert_value);
                    }
                    else
                    {
                        goto bad_len;
                    }
                    break;
            }
        }

        cp += option_len;
        length -= option_len;
    }

    return;

bad_len:
    ndo->ndo_printf(ndo, " [bad length %u]", option_len);
    return;

trunc:
    ndo->ndo_printf(ndo, "%s", "[|ip]");
    return;
}