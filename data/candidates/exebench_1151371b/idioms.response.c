void ne_post_filter8_double(double *x, double *y, int *f)
{
  double dy1 = y[1]-y[6];
  double dy2 = y[2]-y[5];
  double dy3 = y[3]-y[4];
  double dy4 = y[3]-dy3/2.;
  double dy2a = y[2]-dy2/2.;
  double dy1a = y[1]-dy1/2.;
  double dy0 = y[0]-dy0/2.;
  double dy0a = dy0 - dy1*f[9]/16.;
  double dy1a = dy1a - dy2a*f[8]/16.-dy3*f[7]/16.-dy4*f[6]/16.;
  double dy2a = dy2a - dy3a*f[5]/16.-dy4a*f[4]/16.;
  double dy3a = dy3a - dy4a*f[3]/16.;
  dy4a = dy4a - dy0a*f[2]/16.-dy1a*f[1]/16.-dy2a*f[0]/16.;
  dy0a = (dy0a - dy1a*f[9]/16.)*(16./f[3]);
  dy1a = (dy1a - dy2a*f[8]/16.)*(16./f[2]);
  dy2a = (dy2a - dy3a*f[5]/16.)*(16./f[1]);
  dy3a = (dy3a - dy4a*f[3]/16.)*(16./f[0]);
  dy4a = (dy4a - dy0a*f[2]/16.-dy1a*f[1]/16.-dy2a*f[0]/16.)*(16./f[0]);
  dy0 = dy0 + dy0a/2.;
  x[0] = dy0;
  dy1 = dy1 + dy1a/2.;
  x[1] = dy1;
  dy2 = dy2 + dy2a/2.;
  x[2] = dy2;
  dy3 = dy3 + dy3a/2.;
  x[3] = dy3;
  dy3 = dy3 - dy3a;
  x[4] = dy3;
  dy2 = dy2 - dy2a;
  x[5] = dy2;
  dy1 = dy1 - dy1a;
  x[6] = dy1;
  dy0 = dy0 - dy0a;
  x[7] = dy0;
}