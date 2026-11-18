void FindDivDiff5Coeff2(double a, double b, double c, double d, double *dd)
{
  double ab,ac,ad,bc,bd,cd;

  ab = 1.0/(b-a);
  ac = 1.0/(c-a);
  ad = 1.0/(d-a);
  bc = 1.0/(c-b);
  bd = 1.0/(d-b);
  cd = 1.0/(d-c);

  dd[0] = -ab*ab*ac*ac*ad;
  dd[1] = -(2.0*bc+bd-ab)*ab*bc*bc*bd;
  dd[2] = -ab*bc*bc*bd;
  dd[3] = -(cd-2.0*bc-ac)*ac*bc*bc*cd;
  dd[4] = -ac*bc*bc*cd;
  dd[5] = ad*bd*bd*cd*cd;
}