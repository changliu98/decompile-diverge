void __cdecl cpuid(int op, unsigned int *eax_0, unsigned int *ebx_0, unsigned int *ecx_0, unsigned int *edx_0)
{
    unsigned int a, b, c, d;
    
    __asm__ __volatile__(
        "cpuid"
        : "=a"(a), "=b"(b), "=c"(c), "=d"(d) // Output operands mapped to registers
        : "a"(op)                            // Input operand mapped to RAX/EAX
    );
    
    *eax_0 = a;
    *ebx_0 = b;
    *ecx_0 = c;
    *edx_0 = d;
}