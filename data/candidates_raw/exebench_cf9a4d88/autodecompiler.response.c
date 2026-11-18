int copy_struct11(struct test11 *dest, struct test11 *src)
{
 dest->a = src->a & 0x7fffffffffffffff;
 dest->b = src->b;

 return 1;
}