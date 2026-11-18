void GetCPUInfo(uint32_t *info, uint32_t leaf) {
    uint32_t eax, ebx, ecx, edx;
    
    // Execute the CPUID instruction with the given leaf in EAX.
    // The compiler will handle the input/output registers for the inline assembly.
    __asm__ __volatile__(
        "cpuid"
        : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
        : "a" (leaf)
    );
    
    // Store the results into the output array
    info[0] = eax;
    info[1] = ebx;
    info[2] = ecx;
    info[3] = edx;
}