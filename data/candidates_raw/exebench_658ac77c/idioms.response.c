void v3add(struct v3 *a, struct v3 *b, struct v3 *out)
{
  out->x = a->x + b->x;
  out->y = a->y + b->y;
  out->z = a->z + b->z;
}