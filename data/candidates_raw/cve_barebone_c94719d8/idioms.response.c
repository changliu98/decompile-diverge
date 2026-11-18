void ripng_print(struct netdissect_options *ndo, unsigned char *pp, unsigned int length)
{
    int i; int n;
    struct netinfo6 *ni;
    int vers;
    int nreq;
    int nres;
    int nreq_trunc;
    int nres_trunc;
    if (ndo->ndo_snapend < (unsigned char *)pp)
        return;
    n = (length < (unsigned int)(ndo->ndo_snapend - pp))
        ? length : (unsigned int)(ndo->ndo_snapend - pp);
    if (n < sizeof(struct ripng_hdr))
        return;
    i = n - sizeof(struct ripng_hdr);
    vers = pp[0];
    if (vers == 1) {
        nreq = n / sizeof(struct ripng_req);
        if (nreq == 1 && pp[sizeof(struct ripng_req) - 1] == 0x10) {
            int allzero = 1;
            if (pp[sizeof(struct ripng_req) * 0] != 0)
                allzero = 0;
            if (pp[sizeof(struct ripng_req) * 1] != 0)
                allzero = 0;
            if (pp[sizeof(struct ripng_req) * 2] != 0)
                allzero = 0;
            if (pp[sizeof(struct ripng_req) * 3] != 0)
                allzero = 0;
            if (allzero)
                ndo->ndo_printf(ndo, " ripng-req dump");
        }
        if (nreq * sizeof(struct ripng_req) == n - sizeof(struct ripng_hdr))
            ndo->ndo_printf(ndo, " ripng-req %d:", nreq);
        else
            ndo->ndo_printf(ndo, " ripng-req %d[%u]:", nreq, n);
        ni = (struct netinfo6 *) (pp + sizeof(struct ripng_hdr));
        while (i >= sizeof(struct ripng_req)) {
            if (ndo->ndo_vflag > 1)
                ndo->ndo_printf(ndo, "\n\t");
            else
                ndo->ndo_printf(ndo, " ");
            ripng_req_print(ndo, ni, 0);
            i -= sizeof(struct ripng_req);
            ni++;
        }
    } else if (vers == 2) {
        nres = n / sizeof(struct ripng_res);
        if (nres * sizeof(struct ripng_res) == n - sizeof(struct ripng_hdr))
            ndo->ndo_printf(ndo, " ripng-resp %d:", nres);
        else
            ndo->ndo_printf(ndo, " ripng-resp %d[%u]:", nres, n);
        ni = (struct netinfo6 *) (pp + sizeof(struct ripng_hdr));
        nres_trunc = 0;
        while (i >= sizeof(struct ripng_res)) {
            if (ndo->ndo_vflag > 1)
                ndo->ndo_printf(ndo, "\n\t");
            else
                ndo->ndo_printf(ndo, " ");
            ripng_res_print(ndo, ni, ni->rip6_metric);
            i -= sizeof(struct ripng_res);
            ni++;
        }
        if (nres_trunc)
            ndo->ndo_printf(ndo, "[|ripng]");
    } else
        ndo->ndo_printf(ndo, " ripng-%d ?? %u", vers, n);
    if (pp[1] != 1)
        ndo->ndo_printf(ndo, " [vers %d]", pp[1]);
}