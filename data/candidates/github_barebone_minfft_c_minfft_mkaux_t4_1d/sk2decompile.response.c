minfft_aux_t *minfft_mkaux_t4_1d(int n) {
  minfft_aux_t *x;
  int i;
  double *p;
  if (n <= 0 || (n & (n - 1)) != 0) return NULL;
  x = (minfft_aux_t *)malloc(sizeof(minfft_aux_t));
  if (x == NULL) goto error;
  x->n = n;
  if (n >= 2) {
    x->w = (double *)malloc(2 * (n / 2) * sizeof(double));
    if (x->w == NULL) goto error;
    x->t = (double *)malloc(2 * (n + n / 2) * sizeof(double));
    if (x->t == NULL) goto error;
    p = x->t;
    for (i = 0; i < n / 2; i++) {
      *p++ = ncos(-i, 2 * n);
      *p++ = nsin(-i, 2 * n);
    }
    for (i = 0; i < n; i++) {
      *p++ = ncos(-(2 * i + 1), 8 * n);
      *p++ = nsin(-(2 * i + 1), 8 * n);
    }
    x->dft = minfft_mkaux_dft_1d(n / 2);
    if (x->dft == NULL) goto error;
  } else {
    x->w = NULL;
    x->t = NULL;
    x->dft = NULL;
  }
  x->dfti = NULL;
  return x;
error:
  minfft_free_aux(x);
  return NULL;
}