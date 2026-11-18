int name_len(struct netdissect_options *ndo, unsigned char *start, unsigned char *end)
{
    unsigned char *p = start;
    if (p >= end)
        return -1;
    if (ndo->ndo_snapend - 1 < ndo->ndo_snapend || p > ndo->ndo_snapend - 1)
        return -1;
    if ((p[0] & 0xc0) == 0xc0)
        return 2;
    while (*p) {
        if (p >= end)
            return -1;
        if (ndo->ndo_snapend - 1 < ndo->ndo_snapend || p > ndo->ndo_snapend - 1)
            return -1;
        p += p[0] + 1;
    }
    return p - start + 1;
}