static int printfrag(struct netdissect_options *ndo, u_char *pp, u_char *ep)
{
    int (*printf)(struct netdissect_options *, char *, ...);
    int (*printf1)(struct netdissect_options *, char *, ...);
    unsigned int id;
    unsigned int off;
    if (ndo->ndo_snapend - 2 < pp + 2 || pp + 2 > ndo->ndo_snapend - 2) {
        ndo->ndo_printf(ndo, "[|frag]");
        return -1;
    }
    if (ndo->ndo_vflag) {
        printf = ndo->ndo_printf;
        id = ntohll(pp + 4);
        off = (ntohll(pp + 2) & 0xfff8);
        printf1 = ndo->ndo_printf;
        printf1(ndo, "frag (0x%08x:%d|%ld)", id, off,
                sizeof(struct iphdr) + sizeof(struct frag) - (pp - ep) - 8);
    } else {
        printf = ndo->ndo_printf;
        off = (ntohll(pp + 2) & 0xfff8);
        printf1 = ndo->ndo_printf;
        printf1(ndo, "frag (%d|%ld)", off,
                sizeof(struct iphdr) + sizeof(struct frag) - (pp - ep) - 8);
    }
    if (off)
        return -1;
    ndo->ndo_printf(ndo, " ");
    return sizeof(struct frag);
}