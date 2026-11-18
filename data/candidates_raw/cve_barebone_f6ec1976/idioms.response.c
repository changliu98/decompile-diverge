static void print_caps(struct netdissect_options *ndo, unsigned char *caps, int caps_len)
{
    int i;
    int cap_type; int cap_len; int tcap_len; int cap_offseta;
    int (*ndo_printf)(struct netdissect_options *ndo, char *fmt, ...);
    int (*ndo_printfa)(struct netdissect_options *ndo, char *fmt, ...);
    int (*ndo_printfb)(struct netdissect_options *ndo, char *fmt, ...);
    for (i = 0; i < caps_len; i += (cap_len + 2)) {
        if (ndo->ndo_snapend - 2 < ndo->ndo_snapend ||
            caps + i > ndo->ndo_snapend - 2)
            goto trunc;
        cap_type = caps[i];
        cap_len = caps[i + 1];
        tcap_len = cap_len;
        ndo_printf = ndo->ndo_printf;
        ndo_printf(ndo, "\n\t      %s (%u), length: %u",
            str_from_index(bgp_capcode_values, "Unknown", cap_type),
            cap_type, cap_len);
        if (ndo->ndo_snapend - cap_len < ndo->ndo_snapend ||
            caps + i + 2 > ndo->ndo_snapend - cap_len)
            goto trunc;
        switch (cap_type) {
        case 1:
            ndo_printfa = ndo->ndo_printf;
            ndo_printfa(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u)",
                str_from_index(af_values, "Unknown",
                    ((unsigned int) (((unsigned char *) (caps + i + 2))[0]) << 8 | ((unsigned int) (((unsigned char *) (caps + i + 2))[1])) & 0xff),
                    ((unsigned int) (((unsigned char *) (caps + i + 2))[0]) << 8 | ((unsigned int) (((unsigned char *) (caps + i + 2))[1])) & 0xff)),
                ((unsigned int) (((unsigned char *) (caps + i + 2))[0]) << 8 | ((unsigned int) (((unsigned char *) (caps + i + 2))[1])) & 0xff),
                str_from_index(bgp_safi_values, "Unknown", caps[i + 2 + 2]),
                caps[i + 2 + 2]);
            break;
        case 2:
            break;
        case '@':
            if (ndo->ndo_snapend - 2 < ndo->ndo_snapend ||
                caps + i + 2 > ndo->ndo_snapend - 2)
                goto trunc;
            ndo_printf(ndo, "\n\t\tRestart Flags: [%s], Restart Time %us",
                caps[i + 2] & 0x80 ? "R" : "none",
                ((unsigned int) (((unsigned char *) (caps + i + 2))[0]) << 8 | ((unsigned int) (((unsigned char *) (caps + i + 2))[1])) & 0xff) & 0xfff);
            cap_len -= 2;
            cap_offseta = 2 + 2;
            while (cap_len >= 2 + 2) {
                ndo_printfa = ndo->ndo_printf;
                ndo_printfa(ndo, "\n\t\t  AFI %s (%u), SAFI %s (%u), "
                    "Forwarding state preserved: %s",
                    str_from_index(af_values, "Unknown",
                        ((unsigned int) (((unsigned char *) (caps + i + cap_offseta))[0]) << 8 | ((unsigned int) (((unsigned char *) (caps + i + cap_offseta))[1])) & 0xff),
                        ((unsigned int) (((unsigned char *) (caps + i + cap_offseta))[0]) << 8 | ((unsigned int) (((unsigned char *) (caps + i + cap_offseta))[1])) & 0xff)),
                    ((unsigned int) (((unsigned char *) (caps + i + cap_offseta))[0]) << 8 | ((unsigned int) (((unsigned char *) (caps + i + cap_offseta))[1]))