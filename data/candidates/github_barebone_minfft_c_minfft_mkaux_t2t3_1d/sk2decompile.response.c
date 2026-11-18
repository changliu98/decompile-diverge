minfft_aux_t2t3_1d_t *minfft_mkaux_t2t3_1d(int n) {
  minfft_aux_t2t3_1d_t *aux;
  int i;
  real *p;
  if (n <= 0 || (n & (n - 1)) != 0) return NULL;
  aux = (minfft_aux_t2t3_1d_t *)malloc(sizeof(minfft_aux_t2t3_1d_t));
  if (aux == NULL) goto err;
  aux->n = n;
  if (n >= 2) {
    aux->w = (real *)malloc((n + 2) * sizeof(real));
    if (aux->w == NULL) goto err;
    aux->t = (real *)malloc((n / 2) * 2 * sizeof(real));
    if (aux->t == NULL) goto err;
    p = aux->t;
    for (i = 0; i < n / 2; i++) {
      *p++ = ncos(-i, 4 * n);
      *p++ = nsin(-i, 4 * n);
    }
  } else {
    aux->w = NULL;
    aux->t = NULL;
  }
  aux->aux_dft = minfft_mkaux_realdft_1d(n);
  if (aux->aux_dft == NULL) goto err;
  aux->aux_fft = NULL;
  return aux;
err:
  minfft_free_aux((minfft_aux_t *)aux);
  return NULL;
}