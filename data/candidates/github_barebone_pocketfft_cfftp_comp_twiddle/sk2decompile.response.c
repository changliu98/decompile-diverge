int cfftp_comp_twiddle(cfft_plan_t *p) {
  unsigned int n = p->n;
  double *tw = malloc(2 * n * sizeof(double));
  if (tw == NULL) return -1;
  sincos_2pibyn(n, tw);
  unsigned int n_prev = 1;
  unsigned int n_tw = 0;
  for (unsigned int i = 0; i < p->n_dim; i++) {
    unsigned int n_d = p->dim[i].n;
    unsigned int n_tw_d = n / (n_d * n_prev);
    p->dim[i].tw = p->tw_buf + n_tw;
    n_tw += (n_tw_d - 1) * (n_d - 1);
    for (unsigned int j = 1; j < n_d; j++) {
      for (unsigned int k = 1; k < n_tw_d; k++) {
        p->dim[i].tw[k - 1 + (j - 1) * (n_tw_d - 1)].re =
            tw[2 * j * k * n_prev];
        p->dim[i].tw[k - 1 + (j - 1) * (n_tw_d - 1)].im =
            tw[2 * j * k * n_prev + 1];
      }
    }
    if (n_d > 11) {
      p->dim[i].tw_d = p->tw_buf + n_tw;
      n_tw += n_d;
      for (unsigned int j = 0; j < n_d; j++) {
        p->dim[i].tw_d[j].re = tw[2 * j * n_tw_d * n_prev];
        p->dim[i].tw_d[j].im = tw[2 * j * n_tw_d * n_prev + 1];
      }
    }
    n_prev *= n_d;
  }
  free(tw);
  return 0;
}