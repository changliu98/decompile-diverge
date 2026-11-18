int rfftp_forward(rfft_plan_1d p, double *a, double normfac) {
  unsigned int n, m, vl, i, j, r;
  double *tmp, *a1, *a2;
  if (p->n == 1) return 0;
  n = p->n;
  m = n;
  vl = p->vl;
  tmp = (double *)malloc(n * sizeof(double));
  if (tmp == NULL) return -1;
  a1 = a;
  a2 = tmp;
  for (i = 0; i < vl; i++) {
    j = vl - i - 1;
    r = p->v[j].r;
    m = n / m;
    m /= r;
    switch (r) {
      case 2:
        radf2(m, m, a1, a2, p->v[j].w);
        break;
      case 3:
        radf3(m, m, a1, a2, p->v[j].w);
        break;
      case 4:
        radf4(m, m, a1, a2, p->v[j].w);
        break;
      case 5:
        radf5(m, m, a1, a2, p->v[j].w);
        break;
      default:
        radfg(m, r, m, a1, a2, p->v[j].w, p->v[j].fg);
        {
          double *t = a1;
          a1 = a2;
          a2 = t;
        };
        break;
    }
    {
      double *t = a1;
      a1 = a2;
      a2 = t;
    };
  }
  copy_and_norm(a, a1, n, normfac);
  free(tmp);
  return 0;
}