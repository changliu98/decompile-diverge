void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t a, b, c, d;

    // The inline assembly executes the CPUID instruction.
    // 'leaf' is passed in EAX.
    // The outputs are stored in EAX, EBX, ECX, and EDX.
    // EBX is saved and restored because it is callee-saved in the System V AMD64 ABI.
    __asm__ volatile (
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "a" (leaf)
    );

    // Dereference the output pointers and store the results
    if (eax) *eax = a;
    if (ebx) *ebx = b;
    if (ecx) *ecx = c;
    if (edx) *edx = d;
}