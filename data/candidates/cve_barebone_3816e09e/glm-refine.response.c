int __cdecl mobility_opt_print(netdissect_options *ndo, const u_char *bp, const unsigned int len)
{
    unsigned int i = 0;

    while (1)
    {
        // 1. Bounds check: current pointer
        if (i >= len)
            return 0;
        if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || &bp[i] > ndo->ndo_snapend - 1)
            return 1;

        // 2. Determine option length
        unsigned int optlen;
        if (bp[i] != 0)
        {
            // Check if we can read the length byte
            if (i + 1 >= len || ndo->ndo_snapend - 1 > ndo->ndo_snapend || &bp[i + 1] > ndo->ndo_snapend - 1)
                return 1;
            optlen = bp[i + 1] + 2;
        }
        else
        {
            optlen = 1; // Pad1 option
        }

        // 3. Bounds check: entire option fits in buffer and captured data
        if (optlen + i > len || ndo->ndo_snapend - 1 > ndo->ndo_snapend || &bp[optlen + i] > ndo->ndo_snapend - 1)
            return 1;

        // 4. Parse and print option based on type
        switch (bp[i])
        {
            case 0u: // Pad1
                ndo->ndo_printf(ndo, "(pad1)");
                break;

            case 1u: // PadN
                if (len - i < 2)
                {
                    ndo->ndo_printf(ndo, "(padn: trunc)");
                    return 1;
                }
                ndo->ndo_printf(ndo, "(padn)");
                break;

            case 2u: // Refresh
                if (len - i < 4)
                {
                    ndo->ndo_printf(ndo, "(refresh: trunc)");
                    return 1;
                }
                uint16_t refresh_val = EXTRACT_16BITS(&bp[i + 2]);
                ndo->ndo_printf(ndo, "(refresh: %u)", 4 * (unsigned int)refresh_val);
                break;

            case 3u: // Alternate Care-of Address
                if (len - i < 0x12)
                {
                    ndo->ndo_printf(ndo, "(altcoa: trunc)");
                    return 1;
                }
                const char *altcoa_str = getname6(ndo, &bp[i + 2]);
                ndo->ndo_printf(ndo, "(alt-CoA: %s)", altcoa_str);
                break;

            case 4u: // Nonce Indices
                if (len - i < 6)
                {
                    ndo->ndo_printf(ndo, "(ni: trunc)");
                    return 1;
                }
                uint16_t ho_val = EXTRACT_16BITS(&bp[i + 2]);
                uint16_t co_val = EXTRACT_16BITS(&bp[i + 4]);
                ndo->ndo_printf(ndo, "(ni: ho=0x%04x co=0x%04x)", ho_val, co_val);
                break;

            case 5u: // Binding Authorization Data
                if (len - i < 0xC)
                {
                    ndo->ndo_printf(ndo, "(auth: trunc)");
                    return 1;
                }
                ndo->ndo_printf(ndo, "(auth)");
                break;

            default: // Unknown option
                if (len - i < 2)
                {
                    ndo->ndo_printf(ndo, "(sopt_type %u: trunc)", bp[i]);
                    return 1;
                }
                ndo->ndo_printf(ndo, "(type-0x%02x: len=%u)", bp[i], bp[i + 1]);
                break;
        }

        // Advance to the next option
        i += optlen;
    }
}