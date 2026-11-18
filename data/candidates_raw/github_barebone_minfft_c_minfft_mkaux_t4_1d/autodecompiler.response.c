static struct minfft_workspace *minfft_mkaux_dft_1d(int n)
{
  struct minfft_workspace *w;
  double *p;
  int i;
  struct minfft_workspace *w2;

  if (n <= 0 || (n & (n - 1)) != 0) {
    w = NULL;
  } else {
    w = (struct minfft_workspace *)malloc(sizeof(*w));
    if (!w) goto err;
    w->n = n;
    if (n >= 3) {
      w->tw = (double *)malloc(2 * (n / 2) * sizeof(double));
      if (!w->tw) goto err;
      w->wtr = (double *)malloc(2 * (n + n / 2) * sizeof(double));
      if (!w->wtr) goto err;
      p = w->wtr;
      for (i = 0;; ++i) {
        if (i >= n / 2) break;
        *p++ = ncos(2 * n, -i);
        *p++ = nsin(2 * n, -i);
      }
      for (i = 0;; ++i) {
        if (i >= n) break;
        *p++ = ncos(8 * n, -(2 * i + 1));
        *p++ = nsin(8 * n, -(2 * i + 1));
      }
      w2 = minfft_mkaux_dft_1d(n / 2);
      if (!w2) goto err;
      w->w2 = w2;
    } else {
      w->tw = NULL;
      w->wtr = NULL;
      w->w2 = NULL;
    }
    w->w3 = NULL;
  }

  return w;

 err:
  if (w) {
    minfft_free_aux(w);
    w = NULL;
  }
  return w;
}