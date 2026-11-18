void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;
    
    // 'a' is loaded into %eax before the cpuid instruction
    a = leaf;
    
    __asm__ __volatile__(
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d) // Output operands
        : "a" (a)                                // Input operand
    );
    
    // Store the results back into the pointers
    *eax = a;
    *ebx = b;
    *ecx = c;
    *edx = d;
}