double func0(double r,double h)

{
  double dVar1;
  double SA;
  double l;
  double h_local;
  double r_local;
  
  dVar1 = sqrt(r * r + h * h);
  return DAT_00102008 * r * (r + dVar1);
}