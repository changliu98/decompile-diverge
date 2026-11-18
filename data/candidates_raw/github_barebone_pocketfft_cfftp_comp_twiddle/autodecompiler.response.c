int fft_init(struct fft_plan *p)
{
 size_t i, j, k, l1, ido, ip, memofs;
 double *w;
 size_t n = p->n;
 int ret;

 w = malloc(2 * n * sizeof(double));
 if (!w) {
  ret = -1;
  goto err;
 }

 sincos_2pibyn(n, w);

 l1 = 1;
 memofs = 0;
 for (k = 0; k < p->nfactors; k++) {
  ip = p->factors[k].factor;
  ido = n / (l1 * ip);
  p->factors[k].w = &p->w[memofs];
  memofs += (ip - 1) * (ido - 1);
  for (j = 1; j < ip; j++) {
   for (i = 1; i < ido; i++) {
    p->factors[k].w[(j-1)*(ido-1)+(i-1)].real = w[2*j*l1*i];
    p->factors[k].w[(j-1)*(ido-1)+(i-1)].imag = w[2*j*l1*i+1];
   }
  }
  if (ip > 11) {
   p->factors[k].w1 = &p->w[memofs];
   memofs += ip;
   for (j = 0; j < ip; j++) {
    p->factors[k].w1[j].real = w[2*j*l1*ido];
    p->factors[k].w1[j].imag = w[2*j*l1*ido+1];
   }
  }
  l1 *= ip;
 }

 free(w);
 w = NULL;

 ret = 0;

err:
 return ret;
}