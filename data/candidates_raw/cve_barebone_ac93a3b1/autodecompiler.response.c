__attribute__((used)) static int
mp_print_tcp(struct netdissect_options *ndo,
             register const u_char *bp, register u_int length, register u_char th_flags)
{
    register const struct tcphdr *tp = (const struct tcphdr *)bp;
    register int tlen = length;

    if ((tlen != mp_dss_len(tp, 1) && tlen != mp_dss_len(tp, 0)) ||
        (th_flags & 2)) {
        return(0);
    }

    /* XXX: TCP options */
    if (tp->th_flags & 0x10) { (*ndo->ndo_printf)(ndo, " fin"); }
    bp += sizeof(struct tcphdr);

    if (tp->th_flags & 0x01) {
        (*ndo->ndo_printf)(ndo, " ack ");
        if (tp->th_flags & 0x02) {
            (*ndo->ndo_printf)(ndo, "%lu", EXTRACT_64BITS(bp));
            bp += 8;
        } else {
            (*ndo->ndo_printf)(ndo, "%u", EXTRACT_32BITS(bp));
            bp += 4;
        }
    }

    if (tp->th_flags & 0x04) {
        (*ndo->ndo_printf)(ndo, " seq ");
        if (tp->th_flags & 0x08) {
            (*ndo->ndo_printf)(ndo, "%lu", EXTRACT_64BITS(bp));
            bp += 8;
        } else {
            (*ndo->ndo_printf)(ndo, "%u", EXTRACT_32BITS(bp));
            bp += 4;
        }
        (*ndo->ndo_printf)(ndo, " subseq %u", EXTRACT_32BITS(bp));
        bp += 4;
        (*ndo->ndo_printf)(ndo, " len %u", EXTRACT_16BITS(bp));
        bp += 2;
        if (tlen == mp_dss_len(tp, 1)) {
            (*ndo->ndo_printf)(ndo, " csum 0x%x", EXTRACT_16BITS(bp));
        }
    }

    return(1);
}