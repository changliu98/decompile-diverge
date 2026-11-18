void cpuinfo(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;

    // The inline assembly executes the CPUID instruction.
    // 'leaf' is passed in eax.
    // The outputs are stored in eax, ebx, ecx, and edx.
    __asm__ volatile (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "a" (leaf)
    );

    // Dereference the output pointers to store the results
    *eax = a;
    *ebx = b;
    *ecx = c;
    *edx = d;
}