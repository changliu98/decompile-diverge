int exactO(const double z, double *TT, double *Tm, double *qice, double *qbed, double *bmelt) {

  double P_base;

  P_base = 910.0 * 9.81 * 3000.0;


  *Tm = 273.15 - 7.9e-8 * P_base;

  *qice = - 2.10 * (223.15 - *Tm) / 3000.0;


  *qbed = 0.042;


  *bmelt = (0.042 - *qice) / (3.34e5 * 910.0);


  if (z > 3000.0) {
    *TT = 223.15;
  } else if (z >= 0.0) {
    *TT = *Tm + (223.15 - *Tm) * (z / 3000.0);
  } else {
    *TT = *Tm - (0.042 / 3.0) * z;
  }
  return 0;
}