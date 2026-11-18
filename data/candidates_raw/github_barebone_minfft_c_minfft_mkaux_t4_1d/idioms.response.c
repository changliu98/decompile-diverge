struct minfft_aux *minfft_mkaux_t4_1d(int N)
{
    int i;
    struct minfft_aux *aux;
    struct minfft_real *e;
    if (N < 1 || (N & (N - 1)) != 0)
        return ((void *)0);
    aux = (struct minfft_aux *)malloc(sizeof(*aux));
    if (aux == ((void *)0))
        goto fail;
    aux->N = N;
    if (N < 2) {
        aux->t = ((void *)0);
        aux->e = ((void *)0);
        aux->sub1 = ((void *)0);
    } else {
        aux->t = (struct minfft_real *)malloc(sizeof(*aux->t) * (N / 2));
        if (aux->t == ((void *)0))
            goto fail;
        aux->e = (struct minfft_real *)malloc(sizeof(*aux->e) * (N + N / 2));
        if (aux->e == ((void *)0))
            goto fail;
        e = aux->e;
        for (i = 0; i < N / 2; i++) {
            *e++ = ncos(-i, 2 * N);
            *e++ = nsin(-i, 2 * N);
        }
        for (i = 0; i < N; i++) {
            *e++ = ncos(-2 * i - 1, 8 * N);
            *e++ = nsin(-2 * i - 1, 8 * N);
        }
        aux->sub1 = minfft_mkaux_dft_1d(N / 2);
        if (aux->sub1 == ((void *)0))
            goto fail;
    }
    aux->sub2 = ((void *)0);
    return aux;
fail:
    minfft_free_aux(aux);
    return ((void *)0);
}