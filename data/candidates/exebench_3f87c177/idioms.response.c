int matCalcCross(struct v *v1, struct v *v2, struct v *vr)
{
  vr->x = v1->y * v2->z - v1->z * v2->y;
  vr->y = v1->z * v2->x - v1->x * v2->z;
  vr->z = v1->x * v2->y - v1->y * v2->x;
  return 0;
}