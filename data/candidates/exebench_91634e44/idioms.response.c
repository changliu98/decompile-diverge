void qtomat(struct Quaternion *q, float *rot)
{
  rot[0] = q->w * q->w
    + q->x * q->x
    + q->y * q->y
    - q->z * q->z;
  rot[1] = 2 * (q->x * q->y - q->w * q->z);
  rot[2] = 2 * (q->x * q->z + q->w * q->y);
  rot[3] = 2 * (q->y * q->z + q->w * q->x);
  rot[4] = q->w * q->w
    + q->y * q->y
    - q->x * q->x
    - q->z * q->z;
  rot[5] = 2 * (q->y * q->z - q->w * q->x);
  rot[6] = 2 * (q->x * q->z - q->w * q->y);
  rot[7] = 2 * (q->x * q->y + q->w * q->z);
  rot[8] = q->w * q->w
    - q->x * q->x
    - q->y * q->y
    + q->z * q->z;
}