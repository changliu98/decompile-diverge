void __cdecl cpuinfo(int code, int *eax_0, int *ebx_0, int *ecx_0, int *edx_0)
{
    int a, b, c, d;
    
    __asm__ __volatile__ (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d) // Output operands
        : "a" (code)                             // Input operand
    );

    *eax_0 = a;
    *ebx_0 = b;
    *ecx_0 = c;
    *edx_0 = d;
}