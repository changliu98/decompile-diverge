void cpuid_count(uint32_t leaf, uint32_t subleaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;
    
    // The inline assembly executes the CPUID instruction.
    // 'a' and 'c' are used as inputs (leaf and subleaf).
    // '=a', '=b', '=c', '=d' are outputs mapping to eax, ebx, ecx, edx registers.
    // The "cpuid" instruction inherently modifies eax, ebx, ecx, and edx.
    __asm__ volatile (
        "cpuid"
        : "=a"(a), "=b"(b), "=c"(c), "=d"(d)
        : "a"(leaf), "c"(subleaf)
    );
    
    // Store the results back into the caller-provided pointers
    *eax = a;
    *ebx = b;
    *ecx = c;
    *edx = d;
}