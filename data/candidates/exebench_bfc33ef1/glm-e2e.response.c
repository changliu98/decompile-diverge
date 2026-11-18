void cpuid(uint32_t eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx, uint32_t *out_eax) {
    uint32_t a, b, c, d;
    
    // The inline assembly executes the CPUID instruction.
    // 'a' is loaded with the input 'eax' (the leaf parameter).
    // After execution, a, b, c, and d contain the values of EAX, EBX, ECX, and EDX respectively.
    __asm__ volatile (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "a" (eax)
    );
    
    // Dereference the output pointers and store the results
    *ebx = b;
    *ecx = c;
    *edx = d;
    *out_eax = a;
}