struct minfft_aux *minfft_mkaux_realdft_1d(int N)
{
    struct minfft_aux *aux;
    struct minfft_real *e;
    int i;
    if (N < 1 || (N & (N - 1)) != 0)
        return ((void *)0);
    aux = (struct minfft_aux *)malloc(sizeof(*aux));
    if (aux == ((void *)0))
        goto fail;
    aux->N = N;
    if (N < 4) {
        aux->t = ((void *)0);
        aux->e = ((void *)0);
        aux->sub1 = ((void *)0);
    } else {
        aux->t = (struct minfft_real *)malloc(sizeof(*aux->t) * (N / 2));
        if (aux->t == ((void *)0))
            goto fail;
        aux->e = (struct minfft_real *)malloc(sizeof(*aux->e) * (N / 4));
        if (aux->e == ((void *)0))
            goto fail;
        e = aux->e;
        for (i = 0; i < N / 4; i++) {
            *e++ = ncos(-i, N);
            *e++ = nsin(-i, N);
        }
        aux->sub1 = minfft_mkaux_dft_1d(N / 2);
    }
    aux->sub2 = ((void *)0);
    return aux;
fail:
    minfft_free_aux(aux);
    return ((void *)0);
}