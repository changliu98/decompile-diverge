void r3scal(struct vector *v, double c)
{
  v->x = c * v->x;
  v->y = c * v->y;
  v->z = c * v->z;
}