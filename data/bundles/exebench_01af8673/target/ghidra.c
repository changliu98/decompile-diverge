void ecRotate(double *c,double soe,double coe)

{
  double dVar1;
  double e1;
  double coe_local;
  double soe_local;
  double *c_local;
  
  dVar1 = c[2];
  c[2] = c[2] * coe + -(c[1] * soe);
  c[1] = dVar1 * soe + c[1] * coe;
  return;
}