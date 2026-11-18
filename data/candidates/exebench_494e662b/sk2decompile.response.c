void denormF(double *F, double *S, double *T) {
  double s0, s1, s2;
  s0 = T[0];
  s1 = T[1];
  s2 = T[2];
  F[6] += s1 * F[0] + s2 * F[3];
  F[7] += s1 * F[1] + s2 * F[4];
  F[8] += s1 * F[2] + s2 * F[5];
  F[0] *= s0;
  F[1] *= s0;
  F[2] *= s0;
  F[3] *= s0;
  F[4] *= s0;
  F[5] *= s0;
  s0 = S[0];
  s1 = S[1];
  s2 = S[2];
  F[2] += s1 * F[0] + s2 * F[1];
  F[5] += s1 * F[3] + s2 * F[4];
  F[8] += s1 * F[6] + s2 * F[7];
  F[0] *= s0;
  F[3] *= s0;
  F[6] *= s0;
  F[1] *= s0;
  F[4] *= s0;
  F[7] *= s0;
}