static inline void native_cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    // ECX is often used as both an input (sub-leaf) and output register.
    // We save the input ECX value to safely use it before it gets overwritten by the CPUID instruction.
    uint32_t ecx_input = *ecx;

    __asm__ __volatile__(
        "cpuid"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) // Output operands
        : "0"(*eax), "2"(ecx_input)                      // Input operands
    );
}