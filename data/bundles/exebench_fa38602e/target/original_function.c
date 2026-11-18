int params_exactN(double *H0, double *L0, double *xc,
                  double *a, double *Hela, double *k,
                  double *H_xc, double *T_xc) {
  double s;


  *H0 = 3000.0;
  *L0 = 500.0e3;
  *xc = 0.9 * (*L0);


  *a = 0.003 / 31556926.0;
  *Hela = (*H0) / 1.5;


  *k = 9.0 * (*Hela) / ((*a) * (*L0) * (*L0));




  s = (*xc) / (*L0);
  *H_xc = (*H0) * (1.0 - s * s);
  *T_xc = 0.5 * (1.0 - 910.0 / 1028.0) * 910.0 * 9.81 * (*H_xc) * (*H_xc);

  return 0;
}