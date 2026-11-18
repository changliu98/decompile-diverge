void rotate(struct quaternion *q)
{
  int x1r = q->x;
  int x1i = q->y;
  int x2r = q->z;
  int x2i = q->w;
  int x3i = q->x1;
  int x4r = q->y1;
  int x4i = q->z1;
  q->x = q->y1;
  q->y = x3i;
  q->z = x4r;
  q->w = x4i;
  q->x1 = x1r;
  q->y1 = x1i;
  q->z1 = x2r;
  q->w1 = x2i;
}