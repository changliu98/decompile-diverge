void
FindDivDiff5Coeff2(double x0, double x1, double x2, double x3, double *stl)
{
  double m01, m02, m12, m03, m13, m23;

  m01 = 1.0/(x1-x0);
  m02 = 1.0/(x2-x0);
  m12 = 1.0/(x2-x1);
  m03 = 1.0/(x3-x0);
  m13 = 1.0/(x3-x1);
  m23 = 1.0/(x3-x2);

  stl[0] = ((m01)*(m01))*m02*m02*m03;
  stl[1] = ((m13 + 2.0*m12 - m01)*(m01))*m13*m12*m12;
  stl[2] = ((m01)*(m13))*m12*m12;
  stl[3] = ((m23 - 2.0*m12 - m02)*(m23))*m02*m12*m12;
  stl[4] = ((m23)*(m02))*m12*m12;
  stl[5] = ((m03*m13)*m13)*m23*m23;
}