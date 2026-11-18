void denormF(double *F, const double *A1, const double *A2)
{







  double x, y, r;

  r = A2[0];
  x = A2[1];
  y = A2[2];
  F[6] += x * F[0] + y * F[3];
  F[7] += x * F[1] + y * F[4];
  F[8] += x * F[2] + y * F[5];
  F[0] *= r;
  F[1] *= r;
  F[2] *= r;
  F[3] *= r;
  F[4] *= r;
  F[5] *= r;

  r = A1[0];
  x = A1[1];
  y = A1[2];
  F[2] += x * F[0] + y * F[1];
  F[5] += x * F[3] + y * F[4];
  F[8] += x * F[6] + y * F[7];
  F[0] *= r;
  F[3] *= r;
  F[6] *= r;
  F[1] *= r;
  F[4] *= r;
  F[7] *= r;
}