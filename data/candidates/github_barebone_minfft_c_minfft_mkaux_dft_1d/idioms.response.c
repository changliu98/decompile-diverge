struct minfft_aux *minfft_mkaux_dft_1d(int N)
{
  int n; int m;
  struct minfft_aux *aux;
  struct minfft_aux_entry *e;
  m = N;
  if (m < 1 || (m & (m - 1)) != 0)
    return ((void *)0);
  aux = (struct minfft_aux *)malloc(sizeof(minfft_aux));
  if (aux == ((void *)0))
    goto fail;
  aux->N = N;
  if (m >= 16) {
    aux->t = (void *)malloc(sizeof(minfft_aux_entry) * m);
    if (aux->t == ((void *)0))
      goto fail;
    aux->e = (void *)malloc(sizeof(minfft_aux_entry) * m);
    if (aux->e == ((void *)0))
      goto fail;
    e = (struct minfft_aux_entry *)aux->e;
    while (m >= 16) {
      for (n = 0; n < m / 4; n++) {
        e->cos = ncos(-n, m);
        e->sin = nsin(-n, m);
        e->cos2 = ncos(-3 * n, m);
        e->sin2 = nsin(-3 * n, m);
        e++;
      }
      m /= 2;
    }
  } else {
    aux->t = ((void *)0);
    aux->e = ((void *)0);
  }
  aux->sub2 = ((void *)0);
  aux->sub1 = ((void *)0);
  return aux;
fail:
  minfft_free_aux(aux);
  return ((void *)0);
}