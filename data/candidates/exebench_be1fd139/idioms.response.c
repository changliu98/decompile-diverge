void r3sums(struct v *r, struct v *u, double a, struct v *v, double b)
{
  r->x = a * u->x + b * v->x;
  r->y = a * u->y + b * v->y;
  r->z = a * u->z + b * v->z;
}