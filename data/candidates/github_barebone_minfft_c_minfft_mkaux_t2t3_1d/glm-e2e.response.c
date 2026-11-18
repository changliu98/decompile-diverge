struct minfft_aux *minfft_mkaux_t2t3_1d(int N) {
    struct minfft_aux *aux;
    double *t2_ptr;
    int i;

    // Check if N is a power of 2 and greater than 0
    if (N <= 0 || (N & (N - 1)) != 0) {
        return NULL;
    }

    aux = (struct minfft_aux *)malloc(0x28); // 40 bytes
    if (!aux) {
        return NULL;
    }

    aux->N = N;

    if (N >= 2) {
        aux->t1 = malloc((N + 2) * 8);
        if (!aux->t1) {
            free(aux);
            return NULL;
        }

        aux->t2 = malloc((N / 2) * 16);
        if (!aux->t2) {
            free(aux);
            return NULL;
        }

        t2_ptr = (double *)aux->t2;
        for (i = 0; i < N / 2; i++) {
            // The exact arguments to this external function are inferred from 
            // register states (edi = -i, esi = N * 4) before the call.
            t2_ptr[0] = minfft_real(-i, N * 4);
            t2_ptr[1] = minfft_real(-i, N * 4);
            t2_ptr += 2;
        }
    } else {
        aux->t1 = NULL;
        aux->t2 = NULL;
    }

    aux->t3 = minfft_mkaux_t2t3_1d_recursive(N);
    if (!aux->t3) {
        free(aux);
        return NULL;
    }

    aux->t4 = NULL;
    return aux;
}