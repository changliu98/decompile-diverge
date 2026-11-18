
static void
point_computing(double *A_blend,
  double *px, double *py,
  double *x, double *y)
{
  double weights_sum;

  weights_sum = A_blend[0] + A_blend[1] + A_blend[2] + A_blend[3];

  *x = (A_blend[0]*px[0]+A_blend[1]*px[1]+A_blend[2]*px[2]+A_blend[3]*px[3]) / (weights_sum);
  *y = (A_blend[0]*py[0]+A_blend[1]*py[1]+A_blend[2]*py[2]+A_blend[3]*py[3]) / (weights_sum);
}
