static __inline__ void a_or(int *var, int v)
{
   __asm__ __volatile__("lock btr %1,%0":"+m"(*var), "=a"(v) : "0"(v) : "cc", "memory");
}