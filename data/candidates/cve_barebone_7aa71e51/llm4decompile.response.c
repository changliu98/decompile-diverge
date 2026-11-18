const u_char *
smb_fdata(netdissect_options *ndo,
          const u_char *bp,
          const char *fmt,
          const u_char *maxbuf,
          int unicodestr)
{
    const u_char *p;
    char s[128];
    char *cp;
    char *ep;
    int i;

    while (*fmt != '\0') {
        switch (*fmt++) {

        case '#':
            return (bp);

        case '|':
            /*
             * Print the rest of the buffer.
             */
            if (bp < maxbuf) {
                fmt++;
                break;
            }
            return (bp);

        case '*':
            /*
             * Print the next data block.
             */
            while (bp < maxbuf) {
                smb_fdata::depth++;
                p = smb_fdata(ndo, bp, fmt, maxbuf, unicodestr);
                smb_fdata::depth--;
                if (p == NULL)
                    return (NULL);
                if (p == bp)
                    return (bp);
                bp = p;
            }
            return (bp);

        case '[':
            /*
             * Print a data block referenced by an index in the
             * format string.
             */
            if (bp < maxbuf) {
                memset(s, 0, sizeof(s));
                ep = strchr(fmt, ']');
                if (ep - fmt + 1 < sizeof(s)) {
                    strncpy(s, fmt, ep - fmt);
                    s[ep - fmt] = '\0';
                    fmt = ep + 1;
                    bp = smb_fdata1(ndo, bp, s, maxbuf, unicodestr);
                    if (bp == NULL)
                        return (NULL);
                    break;
                }
                return (bp);
            }
            return (bp);

        default:
            /*
             * Print a %c.
             */
            fmt--;
            (*ndo->ndo_printf)(ndo, "%c", *fmt++);
            break;
        }
    }
    if (smb_fdata::depth == 0 && bp < maxbuf) {
        /*
         * Print the rest of the buffer.
         */
        i = maxbuf - bp;
        (*ndo->ndo_printf)(ndo, "Data: (%lu bytes)\n", (unsigned long)i);
        smb_print_data(ndo, bp, i);
        bp += i;
    }
    return (bp);
}