void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
  __asm__ __volatile__ (
    "cpuid"
    :"=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
    :"0"(*eax), "2"(*ecx));
}