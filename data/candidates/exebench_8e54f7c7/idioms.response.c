void cspline2bezier(double *ss, double *ssm)
{
  double m[4][4];
  double *ss_ = ss;
  double *ssm_ = ssm;
  int i; int j;
  memset(m, 0, sizeof(m));
  m[0][0] = 1.0;
  m[0][1] = 1.0;
  m[1][1] = 1.0 / 3.0;
  m[2][2] = 1.0;
  m[2][3] = 1.0;
  m[3][2] = -1.0 / 3.0;
  for (i = 0; i < 4; i++) {
    ss_[i] = 0.0;
    for (j = 0; j < 4; j++) {
      ss_[i] += m[j][i] * ssm_[j];
    }
  }
}