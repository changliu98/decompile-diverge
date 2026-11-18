void __cdecl getCpuid(unsigned int *p, unsigned int ax_0)
{
    __asm__ __volatile__(
        "cpuid"
        : "=a" (p[0]), "=b" (p[1]), "=c" (p[2]), "=d" (p[3]) // Output operands
        : "a" (ax_0)                                          // Input operands
        // rbx, rcx, rdx are implicitly clobbered/used by outputs, 
        // so no explicit clobber list is needed.
    );
}