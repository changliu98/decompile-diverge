void lqtomat(struct quater *q, double rot[3][3])
{
  rot[0][0] = q->w*q->w + q->x*q->x - q->y*q->y - q->z*q->z;
  rot[1][0] = 2*(q->x*q->y - q->w*q->z);
  rot[2][0] = 2*(q->x*q->z + q->w*q->y);
  rot[0][1] = 2*(q->x*q->y + q->w*q->z);
  rot[1][1] = q->w*q->w - q->x*q->x + q->y*q->y - q->z*q->z;
  rot[2][1] = 2*(q->y*q->z - q->w*q->x);
  rot[0][2] = 2*(q->x*q->z - q->w*q->y);
  rot[1][2] = 2*(q->y*q->z + q->w*q->x);
  rot[2][2] = q->w*q->w - q->x*q->x - q->y*q->y + q->z*q->z;
}