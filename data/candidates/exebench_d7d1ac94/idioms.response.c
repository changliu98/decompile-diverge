static int imul_dbl(struct m25519_ge *r, struct m25519_fe *a)
{
  int s = a[0].neg;
  r->y = a;
  r->x = a;
  r->z = a;
  r->t = a;
  return s;
}