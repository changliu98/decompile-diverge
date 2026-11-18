void radius_print_attr(struct netdissect_options *ndo, unsigned char *ap, unsigned int alen, unsigned short code)
{
    unsigned char *p = ap;
    unsigned int len = alen;
    int (*printf)(struct netdissect_options *ndo, char *fmt, ...);
    if (ndo->ndo_snapend - len < p || p > ndo->ndo_snapend) {
        printf = ndo->ndo_printf;
        printf(ndo, "%s", " [|radius]");
        return;
    }
    if (code == 0x3a) {
        printf = ndo->ndo_printf;
        printf(ndo, "%s (0x%02x) ",
               str_index(rfc4675_tagged, "Unknown tag", *p),
               *p);
        p++;
        len--;
    } else if (code >= 0x42 && code <= 0x5a) {
        switch (code) {
        case 0x42:
        case 0x5a:
        case 0x45:
            if (len < 3)
                break;
            if (*p != 0 && *p < 0x20)
                printf(ndo, "Tag[%u] ", *p);
            else
                printf(ndo, "Tag[Unused] ");
            printf(ndo, "Salt %u ", ((unsigned int) *p++ << 8) | *p);
            p += 2;
            len -= 3;
            break;
        }
    }
    if (*p == 0 && len == 0) {
        printf = ndo->ndo_printf;
        printf(ndo, "%s", " [|radius]");
        return;
    }
    if (*p != 0)
        printf(ndo, "Tag[%u] ", *p);
    else
        printf(ndo, "Tag[Unused] ");
    p++;
    len--;
    for (;;) {
        unsigned int c;
        int more = 0;
        if (*p != 0)
            more = len > 0;
        if (!more)
            break;
        if (*p >= ' ' && *p < 0x7f)
            c = *p;
        else
            c = '.';
        printf(ndo, "%c", c);
        p++;
    }
}