static void stack4_replace_top(unsigned long *s, unsigned long e)
{
 *s = (*s & ~0xf) | e;
}