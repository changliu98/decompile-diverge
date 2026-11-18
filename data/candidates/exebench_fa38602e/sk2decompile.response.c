int params_exactN(double *T, double *L, double *Lc, double *nu, double *a,
                  double *b, double *Tc, double *Cpc) {
  *T = 3000.0;
  *L = 500000.0;
  *Lc = 0.9 * *L;
  *nu = 9.506629384623839e-11;
  *a = *T / 1.5;
  *b = 9.0 * *a / (*nu * *L * *L);
  *Tc = *T * (1.0 - (*Lc / *L) * (*Lc / *L));
  *Cpc = 512.3530155642026 * *Tc * *Tc;
  return 0;
}