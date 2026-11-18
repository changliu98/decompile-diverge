void r3sums(double w[3], double u[3], double s, double v[3], double t)
{
  w[0] = u[0]*s + v[0]*t;
  w[1] = u[1]*s + v[1]*t;
  w[2] = u[2]*s + v[2]*t;
}