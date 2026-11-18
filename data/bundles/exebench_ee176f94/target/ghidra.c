int exactO(double z,double *TT,double *Tm,double *qice,double *qbed,double *bmelt)

{
  double P_base;
  double *bmelt_local;
  double *qbed_local;
  double *qice_local;
  double *Tm_local;
  double *TT_local;
  double z_local;
  
  *Tm = DAT_00102040 * DAT_00102030 + DAT_00102038;
  *qice = (DAT_00102020 * (DAT_00102028 - *Tm)) / DAT_00102008;
  *qbed = DAT_00102018;
  *bmelt = (DAT_00102018 - *qice) / DAT_00102010;
  if (z <= DAT_00102008) {
    if (z < 0.0) {
      *TT = z * DAT_00102048 + *Tm;
    }
    else {
      *TT = (DAT_00102028 - *Tm) * (z / DAT_00102008) + *Tm;
    }
  }
  else {
    *TT = DAT_00102028;
  }
  return 0;
}