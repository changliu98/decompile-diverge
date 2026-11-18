void lqtomat(Quaternion* quat, double m[3][3])
{
  m[0][0] = quat->w * quat->w + quat->x * quat->x - quat->y * -quat->y - quat->z * -quat->z;
  m[0][1] = 2 * (quat->x * quat->y - quat->w * -quat->z);
  m[0][2] = 2 * (quat->x * quat->z + quat->w * -quat->y);
  m[1][0] = 2 * (quat->x * quat->y + quat->w * -quat->z);
  m[1][1] = quat->w * quat->w - quat->x * quat->x + quat->y * -quat->y - quat->z * -quat->z;
  m[1][2] = 2 * (quat->y * quat->z - quat->w * -quat->x);
  m[2][0] = 2 * (quat->x * quat->z - quat->w * -quat->y);
  m[2][1] = 2 * (quat->y * quat->z + quat->w * -quat->x);
  m[2][2] = quat->w * quat->w - quat->x * quat->x - quat->y * -quat->y + quat->z * -quat->z;
}