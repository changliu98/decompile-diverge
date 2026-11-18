void __cdecl native_cpuid(unsigned int *eax_0, unsigned int *ebx_0, unsigned int *ecx_0, unsigned int *edx_0)
{
    unsigned int a, b, c, d;
    
    a = *eax_0;
    
    __asm__ __volatile__ (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "a" (a)
    );
    
    *eax_0 = a;
    *ebx_0 = b;
    *ecx_0 = c;
    *edx_0 = d;
}