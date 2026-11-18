void Mat4_RotateQuaternion(float *mat, float *q)
{
  float t0; float t1; float t2; float t3;
  float t4 = -q[0];
  float t5 = -q[1];
  float t6 = -q[2];
  float t7 = -q[3];
  t0 = q[1]*mat[2] + q[2]*mat[1] + q[3]*mat[0] + q[0]*mat[3];
  t1 = q[2]*mat[3] + q[3]*mat[2] + q[0]*mat[1] + q[1]*mat[0];
  t2 = q[3]*mat[0] + q[0]*mat[3] + q[1]*mat[2] + q[2]*mat[1];
  t3 = q[0]*mat[1] + q[1]*mat[0] + q[2]*mat[3] + q[3]*mat[2];
  mat[0] = t0*t4 + t1*t