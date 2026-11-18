void calcula_target (vectori *a, vectori *b, vectori *c)
{
 c->x = b->x + (b->x - a->x);
 c->y = b->y + (b->y - a->y);
}