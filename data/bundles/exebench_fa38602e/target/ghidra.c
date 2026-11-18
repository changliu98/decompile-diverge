int params_exactN(double *H0,double *L0,double *xc,double *a,double *Hela,double *k,double *H_xc,
                 double *T_xc)

{
  double s;
  double *k_local;
  double *Hela_local;
  double *a_local;
  double *xc_local;
  double *L0_local;
  double *H0_local;
  
  *H0 = DAT_00102040;
  *L0 = DAT_00102038;
  *xc = DAT_00102030 * *L0;
  *a = DAT_00102028;
  *Hela = *H0 / DAT_00102020;
  *k = (DAT_00102018 * *Hela) / (*a * *L0 * *L0);
  *H_xc = *H0 * (-(*xc / *L0) * (*xc / *L0) + DAT_00102010);
  *T_xc = DAT_00102008 * *H_xc * *H_xc;
  return 0;
}