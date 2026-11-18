int params_exactN(double *H0, double *L0, double *xc, double *a, double *Hela, double *k, double *H_xc, double *T_xc)
{







  *H0 = 1.0;
  *L0 = 1.0e-6;
  *xc = -0.5 * (*L0);
  *a = 1.0e-4;
  *Hela = *H0 / 1.0e10;
  *k = 8.796 * (*Hela) / ((*a) * (*L0)*(*L0));
  *H_xc = *H0 * (1.0 - (*xc / *L0)*(*xc / *L0));
  *T_xc = 3.0 * (*H_xc) * (*H_xc);
  return 0;
}