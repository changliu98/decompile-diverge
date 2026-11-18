void cpuid_detect(int *has_cpuid, int *has_mmx) {
    int eax, ebx, ecx, edx;

    // Execute CPUID with EAX=1 (Feature Information)
    // The xchg instructions are used to preserve the PIC register (EBX) 
    // by swapping it with ESI, which is a common pattern in 32-bit ABI.
    __asm__ __volatile__(
        "xchg %%esi, %%ebx\n\t"
        "cpuid\n\t"
        "xchg %%esi, %%ebx\n\t"
        : "=a" (eax), "=S" (ebx), "=c" (ecx), "=d" (edx)
        : "a" (1)
    );

    if (has_cpuid != NULL) {
        // Bit 26 of EDX indicates support for SSE2 (often checked alongside MMX)
        *has_cpuid = (edx >> 26) & 1;
    }

    if (has_mmx != NULL) {
        // Bit 0 of ECX indicates support for SSE3 
        // (Note: MMX is typically bit 23 of EDX, but the assembly checks bit 0 of ECX)
        *has_mmx = ecx & 1;
    }
}