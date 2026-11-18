int exactO(double p, double *TT, double *Tm, double *qice, double *qbed, double *bmelt)
{







  double T0 = -50.0;
  double Tc = -0.05;
  double rhoi = 916.8;
  double rhow = 1000.0;
  double L = 3.34e5;
  double cp = 3974.0;
  double K = 2.2e-6;
  double P0 = 1.0e4;
  double g = 9.81;
  double S = 7.5e-4;
  double p_ref = 500.0;

  *Tm = T0 + Tc*(p_ref/P0);
  *qice = rhoi*(Tc - *Tm)/(g*(rhow - rhoi));
  *qbed = L*(*qice)/cp;
  *bmelt = (*qbed - *qice)/(K*P0);

  if (p > P0) {
    *TT = Tc;
  } else if (p >= 0.0) {
    *TT = *Tm + (Tc - *Tm)*(p/P0);
  } else {
    *TT = *Tm + (T0 - *Tm)*(p/P0);
  }

  return 0;
}