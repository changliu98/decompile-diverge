static double s_nd(double *x, double *a)
{
  double y;
  y = *a * *x;
  *x = y;
  return (y * 1.4210854715202e-14);
}