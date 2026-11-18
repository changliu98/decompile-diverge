minfft_aux_t *minfft_mkaux_realdft_1d(int n) {
  minfft_aux_t *a;
  int i;
  double *p;
  if (n <= 0 || (n & (n - 1)) != 0) return NULL;
  a = (minfft_aux_t *)malloc(sizeof(minfft_aux_t));
  if (a == NULL) goto error;
  a->n = n;
  if (n >= 4) {
    a->w = (double *)malloc(sizeof(double) * (n / 2));
    if (a->w == NULL) goto error;
    a->u = (double *)malloc(sizeof(double) * (n / 4));
    if (a->u == NULL) goto error;
    p = a->u;
    for (i = 0; i < n / 4; i++) {
      *p++ = ncos(-i, n);
      *p++ = nsin(-i, n);
    }
    a->d = minfft_mkaux_dft_1d(n / 2);
  } else {
    a->w = NULL;
    a->u = NULL;
    a->d = NULL;
  }
  a->c = NULL;
  return a;
error:
  minfft_free_aux(a);
  return NULL;
}