void __get_cpuid(unsigned int leaf, unsigned int *eax, unsigned int *ebx,
   unsigned int *ecx, unsigned int *edx)
{
 asm ("cpuid"
      : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
      : "a" (leaf));
}