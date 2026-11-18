void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;

    // The cpuid instruction takes the leaf in eax, and returns the results in eax, ebx, ecx, edx.
    // %ebx is a callee-saved register in the System V AMD64 ABI, which is why it's pushed/popped
    // in the assembly prologue/epilogue.
    __asm__ volatile (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d) // Output operands
        : "a" (leaf)                             // Input operands
    );

    *eax = a;
    *ebx = b;
    *ecx = c;
    *edx = d;
}