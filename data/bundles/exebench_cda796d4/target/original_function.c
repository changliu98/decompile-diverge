static inline void
swap(long *p1, long *p2)
{
 long tmp;

 tmp = *p1;
 *p1 = *p2;
 *p2 = tmp;
}