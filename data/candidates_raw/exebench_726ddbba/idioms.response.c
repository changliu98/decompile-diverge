void v_sub(struct vector *a, struct vector *b)
{
  a->x = a->x - b->x;
  a->y = a->y - b->y;
  a->z = a->z - b->z;
}