void cquat_to_matrix_t(Quaternion* quat, double m[3][3])
{
  m[0][0] = 1.0 - 2.0 * (quat->y * quat->y + quat->z * quat->z);
  m[0][1] = 2.0 * (quat->x * quat->y + quat->z * quat->w);
  m[0][2] = 2.0 * (quat->x * quat->z - quat->y * quat->w);
  m[1][0] = 2.0 * (quat->x * quat->y - quat->z * quat->w);
  m[1][1] = 1.0 - 2.0 * (quat->x * quat->x + quat->z * quat->z);
  m[1][2] = 2.0 * (quat->y * quat->z + quat->x * quat->w);
  m[2][0] = 2.0 * (quat->x * quat->z + quat->y * quat->w);
  m[2][1] = 2.0 * (quat->y * quat->z - quat->x * quat->w);
  m[2][2] = 1.0 - 2.0 * (quat->x * quat->x + quat->y * quat->y);
}