int FABSQ(Sleef_quad *r, Sleef_quad *x) {
  r->v0 = x->v0 < 0 ? -x->v0 : x->v0;
  r->v1 = x->v1;
  return 1;
}