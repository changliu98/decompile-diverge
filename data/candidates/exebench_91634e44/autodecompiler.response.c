void qtomat(float* quat, float* mat)
{
  mat[0] = quat[0] * quat[0] + quat[1] * quat[1] - quat[2] * quat[2] - quat[3] * quat[3];
  mat[1] = 2.f * (quat[1] * quat[2] + quat[0] * quat[3]);
  mat[2] = 2.f * (quat[1] * quat[3] - quat[0] * quat[2]);

  mat[3] = 2.f * (quat[1] * quat[2] - quat[0] * quat[3]);
  mat[4] = quat[0] * quat[0] - quat[1] * quat[1] + quat[2] * quat[2] - quat[3] * quat[3];
  mat[5] = 2.f * (quat[2] * quat[3] + quat[0] * quat[1]);

  mat[6] = 2.f * (quat[1] * quat[3] + quat[0] * quat[2]);
  mat[7] = 2.f * (quat[2] * quat[3] - quat[0] * quat[1]);
  mat[8] = quat[0] * quat[0] - quat[1] * quat[1] - quat[2] * quat[2] + quat[3] * quat[3];
}