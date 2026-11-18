void *minfft_mkaux_realdft_1d(int n)
{
    fft_data_t *d;
    double *p;
    int i;
    fft_data_t *r = NULL;

    if ((n <= 0) || ((n & (n - 1)) != 0))
        goto err;

    d = malloc(sizeof(fft_data_t));
    if (!d)
        goto err;
    d->n = n;
    if (n >= 5) {
        d->w = malloc((n / 2) * sizeof(double) * 2);
        if (!d->w)
            goto err;
        d->u = malloc((n / 4) * sizeof(double) * 2);
        if (!d->u)
            goto err;
        p = d->u;
        for (i = 0;; i++) {
            if (i >= (n / 4))
                break;
            *p++ = ncos(0 - i, n);
            *p++ = nsin(0 - i, n);
        }
        d->next = minfft_mkaux_dft_1d(n / 2);
    } else {
        d->w = NULL;
        d->u = NULL;
        d->next = NULL;
    }
    d->next2 = NULL;
    r = d;
err:
    return r;
}