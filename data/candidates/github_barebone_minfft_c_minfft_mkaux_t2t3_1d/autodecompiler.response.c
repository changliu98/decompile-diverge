void *minfft_mkaux_t2t3_1d(int n)
{
    fft_real_object_t *obj;
    double *w;
    int i;

    if (n < 1 || (n & (n - 1)) != 0) {
        obj = NULL;
    } else {
        obj = (fft_real_object_t *)malloc(sizeof(fft_real_object_t));
        if (!obj) goto err;
        obj->n = n;
        if (n > 2) {
            obj->wsave = (double *)malloc((n + 2) * sizeof(double));
            if (!obj->wsave) goto err;
            obj->w = (double *)malloc((n / 2) * 2 * sizeof(double));
            if (!obj->w) goto err;
            w = obj->w;
            for (i = 0;;) {
                do { int j = i; if (j >= n / 2) break; w++[0] = ncos(0 - j, n * sizeof(float)); w++[0] = nsin(0 - j, n * sizeof(float)); ++i; } while (1);
            }
        } else {
            obj->wsave = NULL;
            obj->w = NULL;
        }
        obj->c1 = minfft_mkaux_t2t3_1d(n);
        if (!obj->c1) goto err;
        obj->c2 = NULL;
    }
    return obj;
err:
    if (obj) minfft_free_aux(obj);
    return NULL;
}