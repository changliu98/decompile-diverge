void GivensApply(double c, double s, double *z_1, double *z_2)
{
  double w;
  w = *z_1;
  *z_1 = c*w + s*(*z_2);
  *z_2 = -s*w + c*(*z_2);
}