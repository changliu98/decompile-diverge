struct minfft_aux *minfft_mkaux_t2t3_1d(int N)
{
  struct minfft_aux *aux;
  if (N < 1 || (N - 1) & N)
    return ((void *)0);
  aux = (struct minfft_aux *)malloc(sizeof *aux);
  if (!aux)
    goto err;
  aux->N = N;
  if (N >= 2) {
    aux->t = (double *)malloc((N + 2) * sizeof *aux->t);
    if (!aux->t)
      goto err;
    aux->e = (struct minfft_real *)malloc((N / 2) * sizeof *aux->e);
    if (!aux->e)
      goto err;
    for (int i = 0; i < N / 2; i++) {
      struct minfft_real *e = &aux->e[i];
      e->re = ncos(-i, N * 4);
      e->im = nsin(-i, N * 4);
    }
  } else
    aux->t = aux->e = ((void *)0);
  aux->sub1 = minfft_mkaux_realdft_1d(N);
  if (!aux->sub1)
    goto err;
  aux->sub2 = ((void *)0);
  return aux;
err:
  minfft_free_aux(aux);
  return ((void *)0);
}