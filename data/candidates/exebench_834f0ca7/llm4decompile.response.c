void FindDivDiff5Coeff1(double a, double b, double c, double *dd)
{
  double ab,ac,bc;

  ab = 1.0/(b-a);
  ac = 1.0/(c-a);
  bc = 1.0/(c-b);

  dd[0] = 1.0/6.0*(ab+ac)*ab*ab*ac*ac;
  dd[1] = 1.0/6.0*ab*ab*ac*ac;
  dd[2] = 1.0/6.0*(bc-ab)*bc*bc*ab*ab;
  dd[3] = 1.0/6.0*bc*bc*ab*ab;
  dd[4] = 1.0/12.0*(bc+ac)*bc*bc*ac*ac;
  dd[5] = 1.0/12.0*bc*bc*ac*ac;
}