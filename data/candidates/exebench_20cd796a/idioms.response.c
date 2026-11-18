void cquat_add(struct vec4 *res, struct vec4 *a, struct vec4 *b)
{
  res->x = a->x + b->x;
  res->y = a->y + b->y;
  res->z = a->z + b->z;
  res->w = a->w + b->w;
}