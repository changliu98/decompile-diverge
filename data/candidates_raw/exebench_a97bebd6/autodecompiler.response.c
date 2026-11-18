void add_vectori (vectori *a, vectori *b, vectori *c)
{
 c->x = b->x + (b->x - a->x);
 c->y = b->y + (b->y - a->y);
}