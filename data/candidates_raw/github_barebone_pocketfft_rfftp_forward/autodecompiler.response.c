int fft_exec(FFT_codelet_desc *d, double *data, double scale)
{
  int k, k1, na;
  unsigned long nf, ip, ido, idl1, l1, l2;
  double *in1, *in2, *out1, *out2, *w;

  if (d->n == 1) {
    na = 0;
  } else {
    l1 = d->n;
    ido = l1;
    nf = d->nf;

    out2 = (double *)malloc(sizeof(double) * d->n);
    if (!out2) {na = -1; goto done;}
    in2 = data;
    out1 = out2;
    for (k1=0; k1<nf; ++k1) {
      k = nf - k1 - 1;
      ip = d->f[k].ip;
      idl1 = ido / l1;
      l1 /= ip;
      if (ip == 4) radf4(ido, l1, in2, out1, d->f[k].w);
      else if (ip == 2) radf2(ido, l1, in2, out1, d->f[k].w);
      else if (ip == 3) radf3(ido, l1, in2, out1, d->f[k].w);
      else if (ip == 5) radf5(ido, l1, in2, out1, d->f[k].w);
      else {
 radfg(ido, ip, l1, in2, out1, d->f[k].w, d->f[k].w2);
 {double *tmp = in2; in2 = out1; out1 = tmp;};
      }
      {double *tmp = in2; in2 = out1; out1 = tmp;};
    }

    copy_and_norm(data, in2, scale, d->n);
    free(out2); out2 = 0;
    na = 0;
  }
done:
  return na;
}