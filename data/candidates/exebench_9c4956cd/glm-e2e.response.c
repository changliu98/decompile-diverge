void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;

    // The 'a' and 'c' registers are inputs to cpuid.
    // 'a' is the leaf, and 'c' is the subleaf (which is initialized to 0).
    __asm__ volatile (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d) // outputs
        : "a" (leaf), "c" (0)                   // inputs
    );

    // Store the results into the output pointers
    *eax = a;
    *ebx = b;
    *ecx = c;
    *edx = d;
}