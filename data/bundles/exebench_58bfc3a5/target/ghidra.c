void FindDivDiff4Coeff(double a,double b,double c,double d,double e,double *dd)

{
  double *dd_local;
  double e_local;
  double d_local;
  double c_local;
  double b_local;
  double a_local;
  
  *dd = DAT_00102010 / ((a - b) * (a - c) * (a - d) * (a - e));
  dd[1] = DAT_00102010 / ((b - a) * (b - c) * (b - d) * (b - e));
  dd[2] = DAT_00102010 / ((c - a) * (c - b) * (c - d) * (c - e));
  dd[3] = DAT_00102010 / ((d - a) * (d - b) * (d - c) * (d - e));
  dd[4] = DAT_00102010 / ((e - a) * (e - b) * (e - c) * (e - d));
  return;
}