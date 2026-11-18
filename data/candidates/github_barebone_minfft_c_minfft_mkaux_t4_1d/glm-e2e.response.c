struct minfft_aux *minfft_mkaux_t4_1d(int N) {
    struct minfft_aux *aux;
    double *ptr;
    int i, limit;

    // Check if N is a power of 2 and greater than 0
    if (N <= 0 || (N & (N - 1)) != 0) {
        return NULL;
    }

    aux = (struct minfft_aux *)malloc(sizeof(struct minfft_aux));
    if (!aux) {
        return NULL;
    }

    aux->N = N;

    if (N < 2) {
        aux->t1 = NULL;
        aux->t2 = NULL;
        aux->t3 = NULL;
    } else {
        aux->t1 = alloc_reals(N / 2);
        if (!aux->t1) {
            free(aux);
            return NULL;
        }

        aux->t2 = alloc_reals(N / 2 + N);
        if (!aux->t2) {
            free(aux);
            return NULL;
        }

        ptr = aux->t2;
        limit = N / 2;
        for (i = 0; i < limit; i++) {
            *ptr++ = get_exp(-i, N * 2);
            *ptr++ = get_exp(-i, N * 2);
        }

        for (i = 0; i < N; i++) {
            *ptr++ = get_exp(-(2 * i + 1), N * 8);
            *ptr++ = get_exp(-(2 * i + 1), N * 8);
        }

        aux->t3 = minfft_mkaux_t4_1d(N / 2);
        if (!aux->t3) {
            free(aux);
            return NULL;
        }
    }

    aux->t4 = NULL;
    return aux;
}