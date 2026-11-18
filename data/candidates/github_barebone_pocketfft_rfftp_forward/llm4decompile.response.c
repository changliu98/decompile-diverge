int rfftp_forward(rfftp_plan plan, double *c, double fct)
{
    double *ch;
    double *p1;
    double *p2;
    size_t nf;
    size_t n;
    size_t ido;
    size_t ip;
    size_t k;
    size_t k1;
    size_t l1;

    if (plan->length == 1)
        return 0;

    n = plan->length;
    nf = plan->nfct;

    ch = (double *)malloc(2 * n * sizeof(double));
    if (ch == NULL)
        return -1;

    p1 = c;
    p2 = ch;
    l1 = n;
    for (k1 = 0; k1 < nf; k1++) {
        k = nf - k1 - 1;
        ip = plan[k].ip;
        ido = n / l1;
        l1 = l1 / ip;
        if (ip == 4)
            radf4(ido, l1, p1, p2, plan[k].w);
        else if (ip == 2)
            radf2(ido, l1, p1, p2, plan[k].w);
        else if (ip == 3)
            radf3(ido, l1, p1, p2, plan[k].w);
        else if (ip == 5)
            radf5(ido, l1, p1, p2, plan[k].w);
        else
            radfg(ido, ip, l1, p1, p2, plan[k].w, plan[k].ipphs);

        p1 = p2;
        p2 = ch + n - p2;
    }

    copy_and_norm(c, p1, n, fct);

    free(ch);

    return 0;
}