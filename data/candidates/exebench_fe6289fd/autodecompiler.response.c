static void *xchg8(void **a, void *b)
{
 void *tmp = b;

 tmp = *a;
 *a = tmp;

 return tmp;
}