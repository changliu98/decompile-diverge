void v_scale(double *v1, double c, double *v0)
{
  v1[0] = c * v0[0];
  v1[1] = c * v0[1];
  v1[2] = c * v0[2];
  v1[3] = c * v0[3];
}