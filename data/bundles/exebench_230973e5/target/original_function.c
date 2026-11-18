static inline void a_store(volatile int *p, int x)
{
 __asm__( "movl %1, %0" : "=m"(*p) : "r"(x) : "memory" );
}