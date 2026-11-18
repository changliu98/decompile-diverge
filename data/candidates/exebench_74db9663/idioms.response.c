void zadd(struct point *a, struct point *b, struct point *c)
{
  c->x = a->x + b->x;
  c->y = a->y + b->y;
}