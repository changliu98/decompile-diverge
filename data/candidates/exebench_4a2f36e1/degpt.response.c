void GivensApply(double c,double s,double *z_1,double *z_2)

{
  double dVar1;
  double dVar2;
  double w;
  double *z_2_local;
  double *z_1_local;
  double s_local;
  double c_local;
  
  dVar1 = *z_1;
  dVar2 = *z_2;
  *z_2 = -*z_1 * s + *z_2 * c;
  *z_1 = dVar1 * c + dVar2 * s;
  return;
}