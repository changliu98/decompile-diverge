void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;

    // The cpuid instruction uses eax as the input leaf.
    // It outputs the results into eax, ebx, ecx, and edx.
    __asm__ volatile (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "a" (leaf)
    );

    // Store the results into the output pointers
    *eax = a;
    *ebx = b;
    *ecx = c;
    *edx = d;
}