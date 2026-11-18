struct minfft_aux *minfft_mkaux_dft_1d(int N) {
    struct minfft_aux *aux;
    double *t2;
    int n;

    // Check if N is a power of 2 and greater than 0
    if (N <= 0 || (N & (N - 1)) != 0) {
        return NULL;
    }

    aux = (struct minfft_aux *)malloc(0x28);
    if (!aux) {
        return NULL;
    }

    aux->N = N;

    if (N < 16) {
        aux->t1 = NULL;
        aux->t2 = NULL;
    } else {
        aux->t1 = malloc((long)N * 16);
        if (!aux->t1) {
            free(aux);
            return NULL;
        }

        aux->t2 = malloc((long)N * 16);
        if (!aux->t2) {
            free(aux);
            return NULL;
        }

        t2 = (double *)aux->t2;
        n = N;
        while (n >= 16) {
            int i;
            for (i = 0; i < n / 4; i++) {
                *t2++ = ncos(0 - i, n);
                *t2++ = nsin(0 - i, n);
                *t2++ = ncos(-3 * i, n);
                *t2++ = nsin(-3 * i, n);
            }
            n /= 2;
        }
    }

    aux->t3 = NULL;
    aux->t4 = NULL;

    return aux;
}