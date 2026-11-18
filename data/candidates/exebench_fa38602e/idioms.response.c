int params_exactN(double *H0, double *L0, double *xc, double *a, double *Hela, double *k, double *H_xc, double *T_xc)
{
  *H0 = 3e3;
  *L0 = 5e5;
  *xc = 0.9 * *L0;
  *a = 9.506629384623839e-11;
  *Hela = *H0 / 1.5;
  *k = 9.0 * *Hela / (*a * *L0 * *L0);
  *H_xc = *H0 * (1 - (*xc / *L0) * (*xc / *L0));
  *T_xc = 512.3530155642026 * *H_xc * *H_xc;
  return 0;
}