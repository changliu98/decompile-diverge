
static inline void cpuid(int op, int *eax, int *ebx, int *ecx, int *edx)
{
 asm volatile ("cpuid"
  : "=a" (*eax),
    "=b" (*ebx),
    "=c" (*ecx),
    "=d" (*edx)
  : "0" (op));
}
