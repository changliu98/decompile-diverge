void stack4_push(unsigned_long *s, unsigned_long e)
{
    *s = *s << 4 | e;
}