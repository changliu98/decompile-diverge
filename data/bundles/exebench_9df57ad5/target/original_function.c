static inline void a_store(volatile int *p, int x)
{
 __asm__ __volatile__(
  "mov %1, %0 ; lock ; orl $0,(%%rsp)"
  : "=m"(*p) : "r"(x) : "memory" );
}