void glmMultVectorByInverseMatrix3d(double result[3], const double m[9], const double v[3])
{
  double det;
  double idet;
  double a1, a2, a3, b1, b2, b3, c1, c2, c3;

  a1 = ((m)[(0) + (0)*(3)]); b1 = ((m)[(0) + (1)*(3)]); c1 = ((m)[(0) + (2)*(3)]);
  a2 = ((m)[(1) + (0)*(3)]); b2 = ((m)[(1) + (1)*(3)]); c2 = ((m)[(1) + (2)*(3)]);
  a3 = ((m)[(2) + (0)*(3)]); b3 = ((m)[(2) + (1)*(3)]); c3 = ((m)[(2) + (2)*(3)]);

  det = a1*(b2*c3 - b3*c2) + b1*(c2*a3 - c3*a2) + c1*(a2*b3 - a3*b2);
  idet = 1 / det;

  result[0] = (b2*c3 - b3*c2)*idet*v[0] + (c2*a3 - c3*a2)*idet*v[1] + (a2*b3 - a3*b2)*idet*v[2];
  result[1] = (b3*c1 - b1*c3)*idet*v[0] + (c3*a1 - c1*a3)*idet*v[1] + (a3*b1 - a1*b3)*idet*v[2];
  result[2] = (b1*c2 - b2*c1)*idet*v[0] + (c1*a2 - c2*a1)*idet*v[1] + (a1*b2 - a2*b1)*idet*v[2];
}