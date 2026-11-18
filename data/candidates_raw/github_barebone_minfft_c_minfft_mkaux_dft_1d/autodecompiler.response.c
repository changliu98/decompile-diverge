static struct fft_data *minfft_init(int n)
{
    struct fft_data *d;
    double *p;
    int i, j;

    if (n <= 0 || (n & (n - 1)) != 0) {
        d = NULL;
    } else {
        d = (struct fft_data *)malloc(sizeof(*d));
        if (!d) goto err;
        d->n = n;
        if (n >= 16) {
            d->c = (double *)malloc(2*n*sizeof(double));
            if (!d->c) goto err;
            d->s = (double *)malloc(2*n*sizeof(double));
            if (!d->s) goto err;
            p = d->s;
            for (;;) {
                if (n < 16) break;
                for (i = 0; i < n/4; i++) {
                    *p++ = ncos(-i, n);
                    *p++ = nsin(-i, n);
                    *p++ = ncos(-3*i, n);
                    *p++ = nsin(-3*i, n);
                }
                n /= 2;
            }
        } else {
            d->c = NULL;
            d->s = NULL;
        }
        d->root = NULL;
        d->next = NULL;
    }
    return d;
err:
    minfft_free_aux(d);
    return NULL;
}