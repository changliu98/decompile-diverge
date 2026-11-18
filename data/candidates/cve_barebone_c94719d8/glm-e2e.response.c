void ripng_print(struct netdissect_options *ndo, const uint8_t *cp, unsigned int length) {
    const uint8_t *bp = cp;
    unsigned int len;
    unsigned int n;
    int trunc;
    const uint8_t *ep;

    if (ndo->ndo_snapend < bp) {
        return;
    }

    len = (unsigned int)(ndo->ndo_snapend - bp);
    if (length > len) {
        len = length;
    }

    if (len < 4) {
        return;
    }

    len -= 4;

    uint8_t cmd = *bp;
    if (cmd == 1) {
        // Request
        n = length / 20;
        if (n == 1) {
            if (bp[23] == 16) {
                const uint32_t *p = (const uint32_t *)(bp + 4);
                if (p[0] == 0 && p[1] == 0 && p[2] == 0 && p[3] == 0) {
                    (*ndo->ndo_printf)(ndo, "\n\tRIPng request for all routes");
                    goto out;
                }
            }
        }

        if ((unsigned long)n * 20 != length - 4) {
            (*ndo->ndo_printf)(ndo, "\n\tRIPng request, %u entries, length %u", n, length);
        } else {
            (*ndo->ndo_printf)(ndo, "\n\tRIPng request, %u entries", n);
        }

        trunc = ((len / 20) * 20 != len);
        cp = bp + 4;
        while (len >= 20) {
            if (ndo->ndo_vflag > 1) {
                (*ndo->ndo_printf)(ndo, "\n\t  ");
            } else {
                (*ndo->ndo_printf)(ndo, "\n\t");
            }
            rip6_entry_print(ndo, cp, 0);
            len -= 20;
            cp += 20;
        }
    } else if (cmd == 2) {
        // Response
        n = length / 20;
        if ((unsigned long)n * 20 != length - 4) {
            (*ndo->ndo_printf)(ndo, "\n\tRIPng response, %u entries, length %u", n, length);
        } else {
            (*ndo->ndo_printf)(ndo, "\n\tRIPng response, %u entries", n);
        }

        trunc = ((len / 20) * 20 != len);
        cp = bp + 4;
        while (len >= 20) {
            if (ndo->ndo_vflag > 1) {
                (*ndo->ndo_printf)(ndo, "\n\t  ");
            } else {
                (*ndo->ndo_printf)(ndo, "\n\t");
            }
            rip6_entry_print(ndo, cp, cp[19]);
            len -= 20;
            cp += 20;
        }

        if (trunc) {
            (*ndo->ndo_printf)(ndo, "\n\t[|ripng]");
        }
    } else {
        (*ndo->ndo_printf)(ndo, "\n\tRIPng version %u command %u, length %u", *bp, length);
    }

out:
    if (bp[1] != 1) {
        (*ndo->ndo_printf)(ndo, "\n\tRIPng version %u", bp[1]);
    }
}