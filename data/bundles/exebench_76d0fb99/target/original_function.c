static void stack4_push(unsigned long *s, unsigned long e)
{
 *s = (*s << 4) | e;
}