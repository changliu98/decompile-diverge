static inline unsigned long xchg8(unsigned long *ptr, unsigned long x)
{
 unsigned long __x = (x);
 asm volatile("xchgq %0,%1"
    : "=r" (__x)
    : "m" (*(volatile unsigned long*)(ptr)), "0" (__x)
    : "memory");

 return __x;
}