void vscale(struct vector *r, struct vector *v, double c)
{
  r->x = c * v->x;
  r->y = c * v->y;
  r->z = c * v->z;
}