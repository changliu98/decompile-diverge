void ecRotate(double *vec, double sin_ang, double cos_ang)
{
  double tmp = vec[1]*cos_ang + vec[2]*sin_ang;
  vec[2] = vec[1]*cos_ang - vec[2]*sin_ang;
  vec[1] = tmp;
}