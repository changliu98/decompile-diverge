minfft_plan_t *minfft_mkaux_dft_1d(int n) {
  minfft_plan_t *p;
  int i, m;
  minfft_real *w;
  m = n;
  if (n <= 0 || (n & (n - 1)) != 0) return NULL;
  p = (minfft_plan_t *)malloc(sizeof(minfft_plan_t));
  if (p == NULL) goto error;
  p->n = n;
  if (n >= 16) {
    p->w1 = (minfft_real *)malloc(16 * n * sizeof(minfft_real));
    if (p->w1 == NULL) goto error;
    p->w2 = (minfft_real *)malloc(16 * n * sizeof(minfft_real));
    if (p->w2 == NULL) goto error;
    w = p->w2;
    while (m >= 16) {
      for (i = 0; i < m / 4; i++) {
        w[0] = ncos(-i, m);
        w[1] = nsin(-i, m);
        w[2] = ncos(-3 * i, m);
        w[3] = nsin(-3 * i, m);
        w += 4;
      }
      m /= 2;
    }
  } else {
    p->w1 = NULL;
    p->w2 = NULL;
  }
  p->c = NULL;
  p->d = NULL;
  return p;
error:
  minfft_free_aux(p);
  return NULL;
}