void denormF(double *mat, double *vec, double *rot)
{
  double c = rot[0];
  double s = rot[1];
  double t = rot[2];
  mat[6] = mat[0]*s + mat[3]*t + mat[6]*c;
  mat[7] = mat[1]*s + mat[4]*t + mat[7]*c;
  mat[8] = mat[2]*s + mat[5]*t + mat[8]*c;
  mat[0] = mat[0]*c;
  mat[1] = mat[1]*c;
  mat[2] = mat[2]*c;
  mat[3] = mat[3]*c;
  mat[4] = mat[4]*c;
  mat[5] = mat[5]*c;
  c = rot[0];
  s = rot[1];
  t = rot[2];
  mat[2] = mat[0]*s + mat[1]*t + mat[2]*c;
  mat[5] = mat[3]*s + mat[4]*t + mat[5]*c;
  mat[8] = mat[6]*s + mat[7]*t + mat[8]*c;
  mat[0] = mat[0]*c;
  mat[3] = mat[3]*c;
  mat[6] = mat[6]*c;
  mat[1] = mat[1]*c;
  mat[4] = mat[4]*c;
  mat[7] = mat[7]*c;
}