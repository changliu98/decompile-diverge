void quat2mat(double *q, double *m)
{
  double x = q[1];
  double y = q[2];
  double z = q[3];
  double w = q[0];
  m[0] = 1 - (y*y + z*z);
  m[1] = 2 * (x*y - z*w);
  m[2] = 2 * (x*z + y*w);
  m[3] = 2 * (x*y + z*w);
  m[4] = 1 - (x*x + z*z);
  m[5] = 2 * (y*z - x*w);
  m[6] = 2 * (x*z - y*w);
  m[7] = 2 * (y*z + x*w);
  m[8] = 1 - (x*x + y*y);
}