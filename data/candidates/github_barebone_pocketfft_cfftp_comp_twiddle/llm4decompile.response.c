int cfftp_comp_twiddle(cfftp_plan plan)
{
  size_t n, l1, l2, f, i, j, m, memofs;
  double *t;

  n = plan->length;
  t = (double *)malloc(2*n*sizeof(double));
  if (t == NULL) return -1;

  sincos_2pibyn(n, t);

  l1 = 1;
  memofs = 0;
  for (f = 0; f < plan->nfct; f++) {
    fct_data *p = &plan->fct[f];
    f = p->fct;
    l2 = n/(l1*f);

    p->tw = (cfftp_complex *) (plan->mem + memofs);
    memofs += (f-1)*(l2-1)*sizeof(cfftp_complex);

    for (j = 1; j < f; j++)
      for (i = 1; i < l2; i++) {
        m = (j*l1*i);
        p->tw[(j-1)*(l2-1)+(i-1)].r = t[2*m];
        p->tw[(j-1)*(l2-1)+(i-1)].i = t[2*m+1];
      }

    if (f > 11) {
      p->tws = (cfftp_complex *) (plan->mem + memofs);
      memofs += f*sizeof(cfftp_complex);

      for (j = 0; j < f; j++) {
        m = (j*l1*l2);
        p->tws[j].r = t[2*m];
        p->tws[j].i = t[2*m+1];
      }
    }

    l1 *= f;
  }

  free(t);

  return 0;
}