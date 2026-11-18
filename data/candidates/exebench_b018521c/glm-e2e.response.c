void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;

    // The inline assembly executes the CPUID instruction.
    // 'a' (eax) is passed as both input (leaf) and output.
    // 'b' (ebx), 'c' (ecx), and 'd' (edx) are outputs.
    // 'rbx' is added to the clobber list because it is used by the instruction 
    // and must be preserved according to the System V AMD64 ABI.
    __asm__ volatile (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "a" (leaf)
        : "rbx"
    );

    // Dereference the output pointers and store the results
    *eax = a;
    *ebx = b;
    *ecx = c;
    *edx = d;
}