void cross(double *h, double *u, double *v)
{
  h[0] = u[1]*v[2] - u[2]*v[1];
  h[1] = u[2]*v[0] - u[0]*v[2];
  h[2] = u[0]*v[1] - u[1]*v[0];
}