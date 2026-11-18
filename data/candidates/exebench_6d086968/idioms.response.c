void mat_copy_vector_l3(struct mat *dest, struct mat *src)
{
  dest->a = src->a;
  dest->b = src->b;
  dest->c = src->c;
}