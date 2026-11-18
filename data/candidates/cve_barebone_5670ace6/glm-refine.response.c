void __cdecl vrrp_print(netdissect_options *ndo, const u_char *bp, u_int len, const u_char *bp2, int ttl)
{
    cksum_vec vec[1];
    const char *type_s;
    const char *addr_s;
    char c;
    int i;
    int naddrs;
    uint16_t intvl;
    int auth_type;
    int type;
    int version;
    
    auth_type = 0;

    // Check if 1 byte can be read
    if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || bp > ndo->ndo_snapend - 1)
        goto trunc;

    version = (*bp & 0xF0) >> 4;
    type = *bp & 0xF;
    type_s = tok2str(&type2str, "unknown type (%u)", type);

    ndo->ndo_printf(ndo, "VRRPv%u, %s", (unsigned int)version, type_s);
    if (ttl != 255)
        ndo->ndo_printf(ndo, ", (ttl %u)", (unsigned int)ttl);

    if (version >= 2 && version <= 3 && type == 1)
    {
        // Check if 3 bytes can be read
        if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || bp + 2 > ndo->ndo_snapend - 1)
            goto trunc;

        ndo->ndo_printf(ndo, ", vrid %u, prio %u", bp[1], bp[2]);

        // Check if 6 bytes can be read
        if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || bp + 5 > ndo->ndo_snapend - 1)
            goto trunc;

        if (version == 2)
        {
            auth_type = bp[4];
            ndo->ndo_printf(ndo, ", authtype %s", tok2str(&auth2str, 0LL, auth_type));
            ndo->ndo_printf(ndo, ", intvl %us, length %u", bp[5], len);
        }
        else
        {
            intvl = bp[5] | ((bp[4] & 0xF) << 8);
            ndo->ndo_printf(ndo, ", intvl %ucs, length %u", intvl, len);
        }

        if (!ndo->ndo_vflag)
            return;

        naddrs = bp[3];

        // Check if bp + len is within bounds
        if (ndo->ndo_snapend - len <= ndo->ndo_snapend && bp <= ndo->ndo_snapend - len)
        {
            if (version == 2)
            {
                vec[0].ptr = bp;
                vec[0].len = len;
                if (in_cksum(vec, 1))
                {
                    // Check if 8 bytes can be read
                    if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || bp + 6 > ndo->ndo_snapend - 2)
                        goto trunc;
                    ndo->ndo_printf(ndo, ", (bad vrrp cksum %x)", EXTRACT_16BITS(bp + 6));
                }
            }
            else if (version == 3)
            {
                if ((uint16_t)nextproto4_cksum(ndo, (const struct ip *)bp2, bp, len, len, 0x70u))
                {
                    // Check if 8 bytes can be read
                    if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || bp + 6 > ndo->ndo_snapend - 2)
                        goto trunc;
                    ndo->ndo_printf(ndo, ", (bad vrrp cksum %x)", EXTRACT_16BITS(bp + 6));
                }
            }
        }

        ndo->ndo_printf(ndo, ", addrs");
        if (naddrs > 1)
            ndo->ndo_printf(ndo, "(%d)", (unsigned int)naddrs);
        ndo->ndo_printf(ndo, ":");

        c = 32; // space character
        bp += 8;
        for (i = 0; i < naddrs; ++i)
        {
            // Check if 4 bytes can be read
            if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || bp + 3 > ndo->ndo_snapend - 1)
                goto trunc;

            addr_s = getname(ndo, bp);
            ndo->ndo_printf(ndo, "%c%s", c, addr_s);
            c = 44; // comma character
            bp += 4;
        }

        if (version == 2 && auth_type == 1)
        {
            // Check if 8 bytes can be read
            if (ndo->ndo_snapend - 1 <= ndo->ndo_snapend && bp + 7 <= ndo->ndo_snapend - 1)
            {
                ndo->ndo_printf(ndo, " auth \"");
                if (!fn_printn(ndo, bp, 8u, ndo->ndo_snapend))
                {
                    ndo->ndo_printf(ndo, "\"");
                    return;
                }
                ndo->ndo_printf(ndo, "\"");
            }
        }
    }

trunc:
    ndo->ndo_printf(ndo, "[|vrrp]");
}