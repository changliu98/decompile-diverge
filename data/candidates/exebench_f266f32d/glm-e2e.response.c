void getCpuid(uint32_t *info, uint32_t leaf) {
    uint32_t eax, ebx, ecx, edx;

    // Inline assembly to execute the CPUID instruction.
    // The leaf value is placed in EAX. 
    // The outputs are stored in eax, ebx, ecx, and edx.
    __asm__ __volatile__(
        "cpuid"
        : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
        : "a" (leaf)
    );

    // Store the results into the info array
    info[0] = eax;
    info[1] = ebx;
    info[2] = ecx;
    info[3] = edx;
}